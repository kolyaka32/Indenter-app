/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "getPos.hpp"


GetPosNode::GetPosNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockLongAction),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Save position", "Запомнить точку"}, Height::Main, WHITE, GUI::Aligment::Left) {}

Node* GetPosNode::copy() const {
    return new GetPosNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight()};
}

void GetPosNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void GetPosNode::blit() const {
    Node::blit();
    text.blit();
}

Node* GetPosNode::use() {}

// void StopNode::save(SDL_IOStream* _fout) const {
//     SDL_IOprintf(_fout, "s\n");
// }
