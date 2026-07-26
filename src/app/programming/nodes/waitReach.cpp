/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "waitReach.hpp"
#include "../../device.hpp"


WaitReachNode::WaitReachNode(const Window& _window, float _X, float _Y, const char* _text)
: Node(_window, _X, _Y, Textures::BlockLongWait),
text(_window, _X-rect.w/2/window.getWidth()+0.005, _Y, 
    {"Wait F >           N", "Ждать F >            Н"},
    Height::Main, WHITE, GUI::Aligment::Left),
forceTyper(_window, _X + (LanguagedText::getLanguage()==Language::Russian ? 0.002 : -0.01),
    _Y-0.002, _text, Height::Medium, GUI::Aligment::Left) {}

Node* WaitReachNode::copy() {
    return new WaitReachNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), forceTyper.getString()};
}

void WaitReachNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    forceTyper.move(_X, _Y);
}

void WaitReachNode::checkOff(const Mouse _mouse) {
    forceTyper.checkOff(_mouse);
}

GUI::Code WaitReachNode::click(const Mouse _mouse) {
    if (in(_mouse)){
        if (forceTyper.click(_mouse)) {
            return GUI::Button1;
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

void WaitReachNode::unclick() {
    forceTyper.unclick();
}

void WaitReachNode::type(SDL_Keycode _code) {
    forceTyper.type(_code);
}

void WaitReachNode::writeString(const char* _str) {
    forceTyper.writeString(_str);
}

void WaitReachNode::update(float _mouseX) {
    forceTyper.update(_mouseX);
}

void WaitReachNode::blit() const {
    Node::blit();
    text.blit();
    forceTyper.blit();
}

Node* WaitReachNode::use() {
    float force = SDL_atof(forceTyper.getString());
    device.sendReachForce(force);
    logger.additional("> Set wait force > %f", force);
    return this;
}

Node* WaitReachNode::handleReachForce() const {
    logger.additional("> Forced was exceeded");
    return nextNode;
}

void WaitReachNode::save(SDL_IOStream* _fout) {
    SDL_IOprintf(_fout, "r%s\n", forceTyper.getString());
}
