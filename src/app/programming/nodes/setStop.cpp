/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setStop.hpp"
#include "../../device.hpp"


SetStopNode::SetStopNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, _X-rect.w/2/window.getWidth()+0.005, _Y, {"Stop", "Остановить"}, GUI::Aligment::Left) {}

Node* SetStopNode::copy() {
    return new SetStopNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight()};
}

void SetStopNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void SetStopNode::blit() const {
    Node::blit();
    text.blit();
}

Node* SetStopNode::use() {
    device.sendStop();
    logger.additional("> Stop movement");
    return nextNode;
}

void SetStopNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, 's');
}
