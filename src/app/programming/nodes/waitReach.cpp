/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "waitReach.hpp"


WaitReachNode::WaitReachNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockLongWait),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Wait for the excess", "Ждать превышения"}, Height::Main, WHITE, GUI::Aligment::Left) {}

Node* WaitReachNode::copy() const {
    return new WaitReachNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight()};
}

void WaitReachNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void WaitReachNode::blit() const {
    Node::blit();
    text.blit();
}

Node* WaitReachNode::use() {}

// void StopNode::save(SDL_IOStream* _fout) const {
//     SDL_IOprintf(_fout, "s\n");
// }