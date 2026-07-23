/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setStop.hpp"
#include "../../device.hpp"


StopNode::StopNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, _X-rect.w/2/window.getWidth()+0.005, _Y, {"Stop", "Остановить"},
    Height::Main, WHITE, GUI::Aligment::Left) {}

Node* StopNode::copy() {
    return new StopNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight()};
}

void StopNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void StopNode::blit() const {
    Node::blit();
    text.blit();
}

Node* StopNode::use() {
    device.sendStop();
    return nextNode;
}

void StopNode::save(SDL_IOStream* _fout) const {
    SDL_IOprintf(_fout, "s\n");
}
