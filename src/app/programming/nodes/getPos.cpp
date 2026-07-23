/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "getPos.hpp"
#include "../../device.hpp"


int GetPosNode::number = 0;

GetPosNode::GetPosNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockLongAction),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Save position", "Запомнить точку"},
    Height::Main, WHITE, GUI::Aligment::Left),
pointTexture(window.getTexture(Textures::SubBlock)),
pointText(window, _X+0.04, _Y, {"p%d", "p%d"}, Height::Main, BLACK, GUI::Aligment::Left, number) {
    pointRect.w = pointTexture->w;
    pointRect.h = pointTexture->h;
    pointRect.x = (_X+0.045)*window.getWidth() - pointRect.w/2;
    pointRect.y = _Y*window.getHeight() - pointRect.h/2;
}

void GetPosNode::reset() {
    // Reset remembered state
    legimate = false;
}

Node* GetPosNode::copy() {
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
    window.blit(pointTexture, pointRect);
    pointText.blit();
}

Node* GetPosNode::use() {
    // Send message to get position
    device.sendGetPos();
    return this;
}

Node* GetPosNode::handleGetPos(int _pos) {
    // Save getted position
    position = _pos;
    legimate = true;
    return nextNode;
}

void GetPosNode::save(SDL_IOStream* _fout) {
    SDL_IOprintf(_fout, "p\n");
}
