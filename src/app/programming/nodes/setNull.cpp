/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setNull.hpp"
#include "../../output/collectedData.hpp"


SetNullNode::SetNullNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, {"Set forces null", "Устанока нуля"}, {_X-rect.w/(2*window.getWidth())+0.005f, _Y, .horAli=GUI::Left}) {}

Node* SetNullNode::copy() {
    return new SetNullNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight()};
}

void SetNullNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void SetNullNode::blit() const {
    Node::blit();
    text.blit();
}

Node* SetNullNode::use() {
    collectedData.setForceNullAsLast();
    logger.additional("> Set graph null");
    return nextNode;
}

void SetNullNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, 'u');
}
