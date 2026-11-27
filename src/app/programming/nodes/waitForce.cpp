/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "waitForce.hpp"
#include "../../device.hpp"


WaitForceNode::WaitForceNode(const Window& _window, float _X, float _Y, char _type, const char* _text)
: Node(_window, _X, _Y, Textures::BlockLongWait),
mode(_type - '0'),
text(_window, {"Wait F", "Ждать F"}, {_X-rect.w/2/window.getWidth()+0.005f, _Y, .horAli=GUI::Left}),
moreButton(_window, {">", ">"}, {_X-0.003f, _Y, .height=GUI::Medium, .textColor=BLACK, .backColor=WHITE}),
lessButton(_window, {"<", "<"}, {_X-0.003f, _Y, .height=GUI::Medium, .textColor=BLACK, .backColor=WHITE}),
forceTyper(_window, {_X + (LanguagedText::getLanguage()==Language::Russian ? 0.012f : 0.0f),
    _Y-0.002f, .height=GUI::Medium, .horAli=GUI::Left, .textColor=BLACK, .backColor=WHITE}, 6, _text) {}

Node* WaitForceNode::copy() {
    return new WaitForceNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), char(mode+'0'), forceTyper.getString()};
}

void WaitForceNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    moreButton.move(_X, _Y);
    lessButton.move(_X, _Y);
    forceTyper.move(_X, _Y);
}

void WaitForceNode::checkOff(const Mouse _mouse) {
    forceTyper.checkOff(_mouse);
}

GUI::Code WaitForceNode::click(const Mouse _mouse) {
    if (in(_mouse)){
        if (mode) {
            if (lessButton.in(_mouse)) {
                mode = false;
                return GUI::Button1;
            }
        } else {
            if (moreButton.in(_mouse)) {
                mode = true;
                return GUI::Button1;
            }
        }
        if (forceTyper.click(_mouse)) {
            return GUI::Button2;
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

void WaitForceNode::unclick() {
    forceTyper.unclick();
}

bool WaitForceNode::type(SDL_Keycode _code) {
    return forceTyper.type(_code);
}

bool WaitForceNode::writeString(const char* _str) {
    return forceTyper.writeString(_str);
}

void WaitForceNode::update(float _mouseX) {
    forceTyper.update(_mouseX);
}

void WaitForceNode::blit() const {
    Node::blit();
    text.blit();
    if (mode) {
        lessButton.blit();
    } else {
        moreButton.blit();
    }
    forceTyper.blit();
}

Node* WaitForceNode::use() {
    float force = SDL_atof(forceTyper.getString());
    if (mode) {
        device.sendLoseForce(force);
        logger.additional("> Set wait loose force: %f", force);
    } else {
        device.sendReachForce(force);
        logger.additional("> Set wait exceed force: %f", force);
    }
    return this;
}

Node* WaitForceNode::handleReachForce() const {
    logger.additional("> Force was exceeded");  // !
    return nextNode;
}

void WaitForceNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, NodeType::WaitForce);
    SDL_IOprintf(_fout, " %d %s", mode+'0', forceTyper.getString());
}
