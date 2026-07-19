/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <mutex>
#include "programMenu.hpp"


std::vector<Node*> ProgramMenu::nodes{};
Node* ProgramMenu::currentNode{};

ProgramMenu::ProgramMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Programming", "Программирование"}, 2, Height::Info),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
startButton(_window, _X+_W*0.37, _Y-_H*0.45, 0.03, Textures::ResumePauseButton),
haltButton(_window,  _X+_W*0.45, _Y-_H*0.45, 0.03, Textures::HaltButton),
saveButton(_window,  _X-_W*0.45, _Y-_H*0.45, 0.03, Textures::SaveButton),
loadButton(_window,  _X-_W*0.37, _Y-_H*0.45, 0.03, Textures::LoadButton),
stoppedInfo(_window, _X+_W*0.16, _Y-_H*0.30, {"Program stopped", "Программа остановлена"}, 1000),
selector(_window, _X-_W/3, _Y+_H*0.05, _W/3, _H*0.9),
filterText{"Program file", "Файл программы"},
filter{filterText.getString().c_str(), "prg"} {
    // Getting location
    char* directory = SDL_GetCurrentDirectory();
    SDL_CreateDirectory("scripts");
    snprintf(saveLocation, sizeof(saveLocation), "%sscripts\\script.prg", directory);
    SDL_free(directory);
    reset();
}

void ProgramMenu::reset() {
    nodes.clear();
    currentNode = nullptr;
    holdingNode = nullptr;
    // Add first node
    nodes.emplace_back(new StartNode{window, 0.5, 0.5});
}

void ProgramMenu::deleteNode(Node* _node) {
    // Check all connected nodes
    while (_node) {
        if (_node->isDeletable()) {
            // Update all nodes to check on connected
            for (int i=0; i < nodes.size(); ++i) {
                nodes[i]->disconnect(_node);
            }
            delete _node;
        }
        // Move to next node
        _node = _node->getNext();
    }
}

bool ProgramMenu::click(const Mouse _mouse) {
    if (startButton.in(_mouse)) {
        currentNode = nodes[0];
        return true;
    }
    if (haltButton.in(_mouse)) {
        currentNode = nullptr;
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
    // Check, if start movement of node
    for (unsigned i=0; i < nodes.size(); ++i) {
        if (holdingNode = nodes[i]->take(_mouse)) {
            // Save current pos
            lastPos = _mouse.getPos();
            return true;
        }
    }

    // Check, if create new node
    if (holdingNode = selector.click(_mouse)) {
        lastPos = _mouse.getPos();
        return true;
    }
    return false;
}

void ProgramMenu::unclick(const Mouse _mouse) {
    if (holdingNode) {
        // Check, if delete node
        if (selector.unclick(_mouse)) {
            deleteNode(holdingNode);
            holdingNode = nullptr;
            return;
        }

        // Check, if connect node
        for (int i=0; i < nodes.size(); ++i) {
            // Try crete link to previous node
            if (nodes[i]->connectTo(holdingNode)) {
                return;
            }
        }

        // Standart stop moving
        holdingNode = nullptr; 
    }
}

void ProgramMenu::update(const Mouse _mouse) {
    // Check for movement of node
    if (holdingNode) {
        // Get relative movement
        float x = (_mouse.getX() - lastPos.x) / window.getWidth();
        float y = (_mouse.getY() - lastPos.y) / window.getHeight();
        holdingNode->moveNode(x, y);
        // Update position
        lastPos = _mouse.getPos();
    }

    // Check, if stopped working
    if (currentNode == nullptr && wasWorking) {
        // Show message
        stoppedInfo.reset();
    }
    // Update previous state
    wasWorking = isExecuting();
}

void ProgramMenu::handlePos() {
    currentNode = currentNode->handleGetPos();
}

void ProgramMenu::handleReachPos() {
    currentNode = currentNode->handlReachPos();
}

void ProgramMenu::handleReachForce() {
    currentNode = currentNode->handleReachForce();
}

bool ProgramMenu::isExecuting() {
    return currentNode != nullptr;
}

void ProgramMenu::blit() const {
    background.blit();
    title.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    selector.blit();
    startButton.blit();
    haltButton.blit();
    saveButton.blit();
    loadButton.blit();
    stoppedInfo.blit();

    // Draw program in reverse order
    for (unsigned i = nodes.size(); i > 0; --i) {
        nodes[i-1]->blit();
    }
    // Draw current node highlight
    if (currentNode) {
        currentNode->blitCurrent();
    }
}


static std::mutex saveMutex;

void ProgramMenu::save(void* _userdata, const char* const* _filelist, int _filter) {
    // Check, if all avaliable
    if (_filelist == nullptr || _filter < 0) {
        return;
    }
    // Getting file
    SDL_IOStream* fout = SDL_IOFromFile(*_filelist, "w");
    if (fout == nullptr) {
        return;
    }
    // Locking, while saving
    saveMutex.lock();

    // Writing nodes to it
    /*unsigned pos = 0;
    Node* node = nodes[pos];
    while (node) {
        //
        // Get next node
    }*/

    saveMutex.unlock();
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", *_filelist);
}

void ProgramMenu::load(void* _userdata, const char* const* _filelist, int _filter) {
    // Check, if all avaliable
    if (_filelist == nullptr || _filter < 0) {
        return;
    }
    // Getting file
    SDL_IOStream* fin = SDL_IOFromFile(*_filelist, "r");
    if (fin == nullptr) {
        return;
    }
    // Locking, while saving
    saveMutex.lock();

    // Loading nodes from it
    /*unsigned pos = 0;
    Node* node = nodes[pos];
    while (node) {
        //
        // Get next node
    }*/

    saveMutex.unlock();
    SDL_CloseIO(fin);
    logger.additional("Program loaded from %s", *_filelist);
}
