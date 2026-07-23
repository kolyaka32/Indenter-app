/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setTarget.hpp"
#include "../../device.hpp"


SetTargetNode::SetTargetNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockLongAction),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Move to", "Двигаться к"},
    Height::Main, WHITE, GUI::Aligment::Left) {}

Node* SetTargetNode::copy() {
    return new SetTargetNode{window, (rect.x + rect.w / 2) / window.getWidth(),
        (rect.y + rect.h / 2) / window.getHeight()};
}

void SetTargetNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void SetTargetNode::blit() const {
    Node::blit();
    text.blit();
}

Node* SetTargetNode::use() {
    // Check if position avaliable
    // !
    // Send move
    //device.sendMoveToPos(pos);
    return this;
}

Node* SetTargetNode::handlReachPos() const {
    // Get at target - move to next node
    return nextNode;
}

void SetTargetNode::save(SDL_IOStream* _fout) {
    // ! Add save of position
    SDL_IOprintf(_fout, "t\n");
}
