/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "halt.hpp"


HaltNode::HaltNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockStop, true, false),
text(_window, _X-rect.w/(2*window.getWidth())+0.03, _Y-0.005, {"Stop", "Стоп"},
    Height::Main, WHITE, GUI::Aligment::Left) {}

Node* HaltNode::copy() {
    return new HaltNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight()};
}

void HaltNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void HaltNode::blit() const {
    Node::blit();
    text.blit();
}

Node* HaltNode::use() {
    logger.additional("> Halt program");
    return nullptr;
}

void HaltNode::save(SDL_IOStream* _fout) {
    SDL_IOprintf(_fout, "h\n");
}
