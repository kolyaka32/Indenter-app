/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "start.hpp"


StartNode::StartNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockStart, false, true, false),
text(_window, {"Start", "Старт"}, {_X-0.02f, _Y, .horAli=GUI::Left}) {}

void StartNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void StartNode::disconnect(const Node* _node) {
    // Can't delete - should check disconnect
    if (nextNode == _node) {
        nextNode = nullptr;
    }
}

void StartNode::blit() const {
    Node::blit();
    text.blit();
}

Node* StartNode::use() {
    logger.additional("> Start program execution");
    return nextNode;
}

void StartNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, 'i');
}
