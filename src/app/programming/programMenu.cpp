/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "programMenu.hpp"


ProgramMenu::ProgramMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H, 10.0),
selector(_window, _X-_W*5/6, _Y, _W/3, _H),
upperRect{(_X-_W/3)*_window.getWidth(), (_X-_W/3)*_window.getHeight(), },
startPauseButton(_window, _X+_W*0.4, _Y+_H*0.05, 0.05, Textures::ResumePauseButton),
haltButton(_window, _X+_W*0.6, _Y+_H*0.05, 0.05, Textures::HaltButton) {
    reset();
}

void ProgramMenu::reset() {
    currentNode = -1;
    holdingNode = -1;
}

bool ProgramMenu::click(const Mouse _mouse) {
    return false;
}

void ProgramMenu::update() {

}

void ProgramMenu::blit() const {
    background.blit();
    selector.blit();
    window.setDrawColor(GREY);
    window.drawRect(upperRect);
    startPauseButton.blit();
    haltButton.blit();
}
