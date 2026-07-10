/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "programMenu.hpp"


ProgramMenu::ProgramMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H, 20.0, 2.0),
title(_window, _X, _Y-_H*0.45, {"Programming", "Программирование"}, 2, Height::Info),
selector(_window, _X-_W/3, _Y+_H*0.05, _W/3, _H*0.9),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
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
    title.blit();
    selector.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    startPauseButton.blit();
    haltButton.blit();
}
