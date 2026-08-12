/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "programMenu.hpp"
#include "../device.hpp"
#include "../../data/cycleTemplate.hpp"


Program ProgramMenu::program{};
unsigned ProgramMenu::autosaveCount = 0;
char* ProgramMenu::saveName = nullptr;
char* ProgramMenu::loadName = nullptr;

ProgramMenu::ProgramMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Programming", "Программирование"},
    2, GUI::Aligment::Midle, Height::Info),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
newButton(_window,   _X-_W*0.45, _Y-_H*0.45, 0.03, Textures::NewButton),
clearOption(_window, 0.5, 0.5, 0.2, 0.2, {"Clear program?", "Очистить программу?"}, {"Yes", "Да"}, {"No", "Нет"}),
saveButton(_window,  _X-_W*0.37, _Y-_H*0.45, 0.03, Textures::SaveButton),
loadButton(_window,  _X-_W*0.29, _Y-_H*0.45, 0.03, Textures::LoadButton),
startButton(_window, _X+_W*0.37, _Y-_H*0.45, 0.03, Textures::ResumePauseButton),
haltButton(_window,  _X+_W*0.45, _Y-_H*0.45, 0.03, Textures::HaltButton),
stoppedInfo(_window, _X+_W*0.16, _Y-_H*0.38, {"Program stopped", "Программа остановлена"}, 1000),
netConnectedInfo(_window, _X+_W*0.16, _Y-_H*0.38, {"Not connected", "Не подключён"}, 1000),
selector(_window, _X-_W/3, _Y+_H*0.05, _W/3, _H*0.9),
filterText{"Program file", "Файл программы"},
filter{filterText.getString().c_str(), "prg"} {
    // Getting location
    char* directory = SDL_GetCurrentDirectory();
    SDL_CreateDirectory("scripts");
    SDL_snprintf(saveLocation, sizeof(saveLocation), "%sscripts\\script.prg", directory);
    SDL_free(directory);

    // Check, if previous save exist
    SDL_PathInfo info;
    char autosaveFile[100];
    SDL_snprintf(autosaveFile, sizeof(autosaveFile), "scripts\\autosave%d.prg",
        (autosaveCount + autosaveMaxCount - 1) % autosaveMaxCount);
    if (SDL_GetPathInfo(autosaveFile, &info)) {
        program.load(window, autosaveFile);
    } else {
        reset();
    }
}

ProgramMenu::~ProgramMenu() {
    // Save as temporary program for load in next seccion
    autosave();
}

void ProgramMenu::reset() {
    holdingNode = nullptr;
    holdingSubNode = nullptr;
}

void ProgramMenu::autosave() {
    // Get new name
    char autosaveFile[100];
    SDL_snprintf(autosaveFile, sizeof(autosaveFile), "scripts\\autosave%d.prg", autosaveCount);
    program.save(autosaveFile);
    // Update counter
    autosaveCount = (autosaveCount + 1) % autosaveMaxCount;
}

bool ProgramMenu::click(const Mouse _mouse) {
    // Check on stop interaction
    selector.checkOff(_mouse);
    program.checkOff(_mouse);
    // Check option box
    if (GUI::Code code = clearOption.click(_mouse)) {
        if (code == GUI::Button1) {
            // Additional save before clearing
            autosave();
            // Clear program
            program.reset(window);
            clearOption.close();
        } else if (code == GUI::Button2) {
            // Close this menu
            clearOption.close();
        }
        return true;
    }
    // Check on buttons press
    if (newButton.in(_mouse)) {
        clearOption.open();
        return true;
    }
    if (saveButton.in(_mouse)) {
        window.showSaveFileDialog(save, &filter, 1, saveLocation);
        return true;
    }
    if (loadButton.in(_mouse)) {
        window.showOpenFileDialog(load, &filter, 1, saveLocation, false);
        return true;
    }
    if (startButton.in(_mouse)) {
        if (device.isConnected()) {
            program.start();
        } else {
            netConnectedInfo.reset();
        }
        return true;
    }
    if (haltButton.in(_mouse)) {
        program.stop();
        return true;
    }
    // Check, if start movement of node
    switch (program.click(_mouse, &holdingNode)) {
    case GUI::Some:
        lastPos = _mouse.getPos();
        logger.additional("Start holding");
        return true;

    case GUI::Activate:
        holdingSubNode = holdingNode->takeSubNode();
        holdingNode = nullptr;
        lastPos = _mouse.getPos();
        logger.additional("Start holding subnode");
        return true;
    
    default:
        break;
    }
    // Check, if create new node
    holdingNode = selector.click(_mouse);
    if (holdingNode) {
        program.add(holdingNode);
        lastPos = _mouse.getPos();
        return true;
    }
    return false;
}

void ProgramMenu::unclick(const Mouse _mouse) {
    if (holdingNode) {
        // Check, if delete node
        if (selector.in(_mouse)) {
            program.deleteNode(holdingNode);
            holdingNode = nullptr;
            logger.additional("Removed node");
            return;
        }
        // Try link holding node (first) to previous node
        if (program.tryConnectTop(holdingNode)) {
            holdingNode = nullptr;
            logger.additional("Connect node top");
            return;
        }
        // Try link last node to others
        if (program.tryConnectBottom(holdingNode)) {
            holdingNode = nullptr;
            logger.additional("Connect node bottom");
            return;
        }
        holdingNode = nullptr; 
    }
    if (holdingSubNode) {
        // Check, if could add subnode
        if (!program.tryConnectSubNode(holdingSubNode)) {
            // Delete this node if unconnected
            delete holdingSubNode;
        }
        holdingSubNode = nullptr;
        return;
    }
    // Check on unclicking on nodes
    selector.unclick();
    program.unclick();
}

void ProgramMenu::type(SDL_Keycode _code) {
    selector.type(_code);
    program.type(_code);
}

void ProgramMenu::writeString(const char* _str) {
    selector.writeString(_str);
    program.writeString(_str);
}

void ProgramMenu::update(const Mouse _mouse) {
    // Update info boxes
    netConnectedInfo.update();
    stoppedInfo.update();
    selector.update(_mouse);

    // Check for movement of node
    if (holdingNode) {
        // Get relative movement
        float dx = (_mouse.getX() - lastPos.x) / window.getWidth();
        float dy = (_mouse.getY() - lastPos.y) / window.getHeight();
        // Move this and connected nodes in reverse order
        Node* moveNode = holdingNode;
        while (moveNode) {
            moveNode->move(dx, dy);
            moveNode = moveNode->getNext();
        }
        // Update position
        lastPos = _mouse.getPos();
    }
    if (holdingSubNode) {
        // Get relative movement
        float dx = (_mouse.getX() - lastPos.x) / window.getWidth();
        float dy = (_mouse.getY() - lastPos.y) / window.getHeight();
        holdingSubNode->move(dx, dy);
        // Update position
        lastPos = _mouse.getPos();
    }

    program.update(_mouse);

    if (program.isStopped()) {
        // Show message
        stoppedInfo.reset();
    }
    // Check on save
    if (saveName) {
        program.save(saveName);
        SDL_free(saveName);
        saveName = nullptr;
    }
    // Check on load
    if (loadName) {
        program.load(window, loadName);
        SDL_free(loadName);
        loadName = nullptr;
    }
}

void ProgramMenu::blit() const {
    background.blit();
    title.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    selector.blit();
    newButton.blit();
    saveButton.blit();
    loadButton.blit();
    startButton.blit();
    haltButton.blit();
    netConnectedInfo.blit();
    stoppedInfo.blit();

    program.blit();
    if (holdingSubNode) {
        holdingSubNode->blit();
    }
    // Top
    clearOption.blit();
}

void ProgramMenu::save(void* _userdata, const char* const* _filelist, int _filter) {
    // Check, if all avaliable
    if (_filelist == nullptr || _filter < 0) {
        return;
    }
    // Write getted name
    SDL_asprintf(&saveName, "%s", *_filelist);
}

void ProgramMenu::load(void* _userdata, const char* const* _filelist, int _filter) {
    // Check, if all avaliable
    if (_filelist == nullptr || _filter < 0) {
        return;
    }
    // Write getted name
    SDL_asprintf(&loadName, "%s", *_filelist);
}
