/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "waitLose.hpp"
#include "../../device.hpp"


WaitLoseNode::WaitLoseNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockLongWait),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Wait for the decrease", "Ждать ослабления"},
    Height::Main, WHITE, GUI::Aligment::Left) {}

Node* WaitLoseNode::copy() {
    return new WaitLoseNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight()};
}

void WaitLoseNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void WaitLoseNode::blit() const {
    Node::blit();
    text.blit();
}

Node* WaitLoseNode::use() {
    // ! Maybe should add force to compare
    device.sendLoseForce(20.0);  // ! Add force input
    return this;
}

Node* WaitLoseNode::handleReachForce() const {
    return nextNode;
}

void WaitLoseNode::save(SDL_IOStream* _fout) {
    SDL_IOprintf(_fout, "d\n");
}
