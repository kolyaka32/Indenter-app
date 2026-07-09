/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "programmingMenu.hpp"


ProgrammingMenu::ProgrammingMenu(const Window& _window, float _X, float _Y, float _H, SDL_FColor _color)
: Template(_window),
points {
    {{_X,          _Y},         {0.0, 0.0, 0.0, 1.0}},
    {{_X,          _Y-_H},      {0.2, 0.0, 0.0, 1.0}},
    {{_X+_H*1,     _Y},         {0.4, 0.0, 0.0, 1.0}},
    {{_X+_H*1,     _Y-_H},      {0.6, 0.0, 0.0, 1.0}},
    {{_X+_H*1.25f, _Y-_H*0.4f}, {0.8, 0.0, 0.0, 1.0}},
    {{_X+_H*1.25f, _Y-_H*1.4f}, {1.0, 0.0, 0.0, 1.0}},
    {{_X+_H*1.5f,  _Y-_H*0.4f}, {1.0, 0.2, 0.0, 1.0}},
    {{_X+_H*1.5f,  _Y-_H*1.4f}, {1.0, 0.4, 0.0, 1.0}},
    {{_X+_H*1.75f, _Y-_H*0.4f}, {1.0, 0.6, 0.0, 1.0}},
    {{_X+_H*1.75f, _Y-_H*1.4f}, {1.0, 0.8, 0.0, 1.0}},
    {{_X+_H*2,     _Y},         {1.0, 1.0, 0.0, 1.0}},
    {{_X+_H*2,     _Y-_H},      {1.0, 1.0, 0.2, 1.0}},
    {{_X+_H*5,     _Y},         {1.0, 1.0, 0.4, 1.0}},
    {{_X+_H*5,     _Y-_H},      {1.0, 1.0, 0.6, 1.0}},
} {}

bool ProgrammingMenu::click(const Mouse mouse) {
    return false;
}

void ProgrammingMenu::update() {

}

void ProgrammingMenu::blit() const  {
    for (int i=0; i < number-2; ++i) {
        // Render each triangule
        window.drawGeometry(points+i, 3);
    }
}
