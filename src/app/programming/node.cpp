/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "node.hpp"


Node::Node(const Window& _window, float _X, float _Y, Textures _texture)
: TextureTemplate(_window, _window.getTexture(_texture)) {
    // Update pos
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = _X;
    rect.y = _Y;
}

bool Node::click(const Mouse mouse) {
    return false;
}

void Node::update() {

}

void Node::blit() const  {
    
}
