/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "pos.hpp"


PosSubNode::PosSubNode(const Window& _window, float _X, float _Y, Node* _sourceNode, int _number)
: Node(_window, _X, _Y, Textures::SubBlock),
text(_window, _X-0.005, _Y, {"p%d", "p%d"}, Height::Main, BLACK, GUI::Aligment::Left, _number),
srcNode(_sourceNode),
number(_number) {}

Node* PosSubNode::copy() {
    return new PosSubNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), srcNode, number};
}

void PosSubNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void PosSubNode::blit() const {
    Node::blit();
    text.blit();
}
