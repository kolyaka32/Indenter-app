/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "pos.hpp"


PosSubNode::PosSubNode(const Window& _window, float _X, float _Y, int _number, Node* _srcNode)
: SubNode(_window, _X, _Y, _srcNode, Textures::SubBlock),
text(_window, _X-0.007, _Y, {"p%d", "p%d"}, Height::Main, BLACK, GUI::Aligment::Left, _number),
number(_number) {}

SubNode* PosSubNode::copy() {
    return new PosSubNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), number, srcNode};
}

void PosSubNode::move(float _X, float _Y) {
    SubNode::move(_X, _Y);
    text.move(_X, _Y);
}

void PosSubNode::blit() const {
    SubNode::blit();
    text.blit();
}
