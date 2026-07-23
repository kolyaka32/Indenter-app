/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setStep.hpp"
#include "../../device.hpp"


SetStepNode::SetStepNode(const Window& _window, float _X, float _Y, const char* _val)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Steping", "Шагать"},
    Height::Main, WHITE, GUI::Aligment::Left),
distanceTyper(_window, _X, _Y, _val, Height::Medium, GUI::Aligment::Left) {}

Node* SetStepNode::copy() {
    return new SetStepNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), distanceTyper.getString()};
}

void SetStepNode::checkOff(const Mouse _mouse) {
    distanceTyper.checkOff(_mouse);
}

GUI::Code SetStepNode::click(const Mouse _mouse) {
    if (in(_mouse)){
        if (distanceTyper.click(_mouse)) {
            return GUI::Button1;
        }
        return GUI::Some;
    }
    return GUI::None;
}

void SetStepNode::unclick() {
    distanceTyper.unclick();
}

void SetStepNode::type(SDL_Keycode _code) {
    distanceTyper.type(_code);
}

void SetStepNode::writeString(const char* _str) {
    distanceTyper.writeString(_str);
}

void SetStepNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    distanceTyper.move(_X, _Y);
}

void SetStepNode::update(float _mouseX) {
    distanceTyper.update(_mouseX);
}

void SetStepNode::blit() const {
    Node::blit();
    text.blit();
    distanceTyper.blit();
}

Node* SetStepNode::use() {
    // Get distance
    float distance = 0.0;
    try {
        float distance = std::stof(distanceTyper.getString());
    } catch (const char* text) {
        return nullptr;
    }
    if (distance > 0) {
        device.sendStepDown(distance);
    } else {
        device.sendStepUp(-distance);
    }
    // Wait until finish
    return this;
}

Node* SetStepNode::handlReachPos() const {
    return nextNode;
}

void SetStepNode::save(SDL_IOStream* _fout) const {
    SDL_IOprintf(_fout, "s\n");
}
