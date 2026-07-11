/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <mutex>
#include "programMenu.hpp"


std::vector<Node*> ProgramMenu::nodes{};

ProgramMenu::ProgramMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Programming", "Программирование"}, 2, Height::Info),
selector(_window, _X-_W/3, _Y+_H*0.05, _W/3, _H*0.9),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
startButton(_window, _X+_W*0.37, _Y-_H*0.45, 0.03, Textures::ResumePauseButton),
haltButton(_window,  _X+_W*0.45, _Y-_H*0.45, 0.03, Textures::HaltButton),
saveButton(_window,  _X-_W*0.45, _Y-_H*0.45, 0.03, Textures::SaveButton),
loadButton(_window,  _X-_W*0.37, _Y-_H*0.45, 0.03, Textures::LoadButton),
filterText{"Program file", "Файл программы"},
filter{filterText.getString().c_str(), "prg"} {
    // Getting location
    char* directory = SDL_GetCurrentDirectory();
    snprintf(saveLocation, sizeof(saveLocation), "%sprograms\\script.prg", directory);
    SDL_free(directory);
    reset();
}

void ProgramMenu::reset() {
    currentNode = -1;
    holdingNode = -1;
}

bool ProgramMenu::click(const Mouse _mouse) {
    if (startButton.in(_mouse)) {
        //
        return true;
    }
    if (haltButton.in(_mouse)) {
        //
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
    // Check, if
    return false;
}

void ProgramMenu::update() {

}

void ProgramMenu::blit() const {
    background.blit();
    title.blit();
    selector.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    startButton.blit();
    haltButton.blit();
    saveButton.blit();
    loadButton.blit();
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
