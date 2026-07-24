/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "subNode.hpp"


SubNode::SubNode(const Window& _window, float _X, float _Y, Node* _srcNode, Textures _texture)
: TextureTemplate(_window, _window.getTexture(_texture)),
srcNode(_srcNode) {
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = _X * window.getWidth() - rect.w/2;
    rect.y = _Y * window.getHeight() - rect.h/2;
}

SubNode::SubNode(const Window& _window, float _X, float _Y, Textures _texture)
: SubNode(_window, _X, _Y, nullptr, _texture) {}

bool SubNode::isNear(const SubNode* _other) const {
    return sqr(rect.x-_other->rect.x) + sqr(rect.y-_other->rect.y) < connectDistance;
}

void SubNode::moveTo(const SubNode* _target) {
    float dx = (_target->rect.x - rect.x) / window.getWidth();
    float dy = (_target->rect.y - rect.y) / window.getHeight();
    move(dx, dy);
}

SubNode* SubNode::copy() {
    return new SubNode{window, rect.x/window.getWidth(), rect.y/window.getHeight(),
        srcNode, Textures::SubBlock};
}

Node* SubNode::getSource() const {
    return srcNode;
}
