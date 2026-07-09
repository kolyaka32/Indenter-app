/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "node.hpp"


Node::Node(const Window& _window, float _X, float _Y, float _H, SDL_FColor _color)
: Template(_window),
points {
    {{_X,          _Y},         _color},
    {{_X,          _Y-_H},      _color},
    {{_X+_H*1,     _Y},         _color},
    {{_X+_H*1,     _Y-_H},      _color},
    {{_X+_H*1.25f, _Y-_H*0.4f}, _color},
    {{_X+_H*1.25f, _Y-_H*1.4f}, _color},
    {{_X+_H*1.75f, _Y-_H*0.4f}, _color},
    {{_X+_H*1.75f, _Y-_H*1.4f}, _color},
    {{_X+_H*2,     _Y},         _color},
    {{_X+_H*2,     _Y-_H},      _color},
    {{_X+_H*5,     _Y},         _color},
    {{_X+_H*5,     _Y-_H},      _color},
} {}

bool Node::click(const Mouse mouse) {
    return false;
}

void Node::update() {

}

void Node::blit() const  {
    for (int i=0; i < number-2; ++i) {
        // Render each triangule
        window.drawGeometry(points+i, 3);
    }
}
