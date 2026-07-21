/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setStep.hpp"


SetStepNode::SetStepNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Steping", "Шагать"}, Height::Main, WHITE, GUI::Aligment::Left) {}


Node* SetStepNode::copy() const {
    return new SetStepNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight()};
}

void SetStepNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void SetStepNode::blit() const {
    Node::blit();
    text.blit();
}

Node* SetStepNode::use() {}

// void StopNode::save(SDL_IOStream* _fout) const {
//     SDL_IOprintf(_fout, "s\n");
// }
