/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "start.hpp"


StartNode::StartNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockStart, false, true, false),
text(_window, _X-0.02, _Y, {"Start", "Старт"}, Height::Main, WHITE, GUI::Aligment::Left) {}

void StartNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void StartNode::disconnect(const Node* _node) {
    if (nextNode == _node) {
        nextNode = nullptr;
    }
}

void StartNode::blit() const {
    Node::blit();
    text.blit();
}

Node* StartNode::use() {
    return nextNode;
}

void StartNode::save(SDL_IOStream* _fout) {
    SDL_IOprintf(_fout, "i\n");
}
