/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "programMenu.hpp"


ProgramMenu::ProgramMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H),
selector(_window) {
    reset();
}

void ProgramMenu::reset() {

}

void ProgramMenu::click(const Mouse mouse) {

}

void ProgramMenu::update() {

}

void ProgramMenu::blit() const {

}
