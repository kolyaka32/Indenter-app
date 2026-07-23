/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "subNode.hpp"


SubNode::SubNode(const Window& _window, float _X, float _Y, int _number, Textures _texture)
: TextureTemplate(_window, _window.getTexture(_texture)),
number(_number) {
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = _X * window.getWidth() - rect.w/2;
    rect.y = _Y * window.getHeight() - rect.h/2;
}

SubNode::SubNode(const Window& _window, float _X, float _Y, Textures _texture)
: SubNode(_window, _X, _Y, -1, _texture) {}

void SubNode::connectSubNode(SubNode* subNode) {
    // !
}

bool SubNode::tryConnectSubNode(SubNode* subNode) {
    // !
    return false;
}

SubNode* SubNode::copy() {
    return new SubNode{window, rect.x/window.getWidth(), rect.y/window.getHeight(),
        number, Textures::SubBlock};
}

int SubNode::getNumber() const {
    return number;
}
