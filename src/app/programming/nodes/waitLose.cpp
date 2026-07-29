/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "waitLose.hpp"
#include "../../device.hpp"


WaitLoseNode::WaitLoseNode(const Window& _window, float _X, float _Y, const char* _text)
: Node(_window, _X, _Y, Textures::BlockLongWait),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y,
    {"Wait F <           N", "Ждать F <            Н"}, GUI::Aligment::Left),
forceTyper(_window, _X + (LanguagedText::getLanguage()==Language::Russian ? 0.002 : -0.01),
    _Y-0.002, _text, GUI::Aligment::Left, Height::Medium)  {}

Node* WaitLoseNode::copy() {
    return new WaitLoseNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), forceTyper.getString()};
}

void WaitLoseNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    forceTyper.move(_X, _Y);
}

void WaitLoseNode::checkOff(const Mouse _mouse) {
    forceTyper.checkOff(_mouse);
}

GUI::Code WaitLoseNode::click(const Mouse _mouse) {
    if (in(_mouse)){
        if (forceTyper.click(_mouse)) {
            return GUI::Button1;
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

void WaitLoseNode::unclick() {
    forceTyper.unclick();
}

void WaitLoseNode::type(SDL_Keycode _code) {
    forceTyper.type(_code);
}

void WaitLoseNode::writeString(const char* _str) {
    forceTyper.writeString(_str);
}

void WaitLoseNode::update(float _mouseX) {
    forceTyper.update(_mouseX);
}

void WaitLoseNode::blit() const {
    Node::blit();
    text.blit();
    forceTyper.blit();
}

Node* WaitLoseNode::use() {
    float force = SDL_atof(forceTyper.getString());
    device.sendLoseForce(force);
    logger.additional("> Set wait force < %f", force);
    return this;
}

Node* WaitLoseNode::handleReachForce() const {
    logger.additional("> Forced was get lower");
    return nextNode;
}

void WaitLoseNode::save(SDL_IOStream* _fout) {
    SDL_IOprintf(_fout, "d%s\n", forceTyper.getString());
}
