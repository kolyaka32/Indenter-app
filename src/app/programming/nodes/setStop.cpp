/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setStop.hpp"


StopNode::StopNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockStop),
text(_window, _X-rect.w/(2*window.getWidth())+0.03, _Y-0.005, {"Stop", "Стоп"}, Height::Main, WHITE, GUI::Aligment::Left) {
}

Node* StopNode::copy() const {
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

Node* StopNode::use() {}

// void StopNode::save(SDL_IOStream* _fout) const {
//     SDL_IOprintf(_fout, "s\n");
// }
