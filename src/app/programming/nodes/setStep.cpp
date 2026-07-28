/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setStep.hpp"
#include "../../device.hpp"


SetStepNode::SetStepNode(const Window& _window, float _X, float _Y, char _speed, const char* _val)
: Node(_window, _X, _Y, Textures::BlockLongAction),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y,
    {"Steping                µm", "Шагать                 мкм"},
    Height::Main, WHITE, GUI::Aligment::Left),
speed(_speed - '0'),
speedRect{(_X-0.017f)*window.getWidth(), _Y*window.getHeight()-18.0f, 32.0, 32.0},
distanceTyper(_window, _X+0.004, _Y-0.002, _val, Height::Medium, GUI::Aligment::Left) {}

Node* SetStepNode::copy() {
    return new SetStepNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), char(speed + '0'), distanceTyper.getString()};
}

void SetStepNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    speedRect.x += _X * window.getWidth();
    speedRect.y += _Y * window.getHeight();
    distanceTyper.move(_X, _Y);
}

void SetStepNode::checkOff(const Mouse _mouse) {
    distanceTyper.checkOff(_mouse);
}

GUI::Code SetStepNode::click(const Mouse _mouse) {
    if (in(_mouse)){
        if (_mouse.in(speedRect)) {
            speed = (speed) % 3 + 1;
            return GUI::Button1;
        }
        if (distanceTyper.click(_mouse)) {
            return GUI::Button2;
        }
        disconnectPrevious();
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

void SetStepNode::update(float _mouseX) {
    distanceTyper.update(_mouseX);
}

void SetStepNode::blit() const {
    Node::blit();
    text.blit();
    distanceTyper.blit();
    // Speed
    switch (speed) {
    case 1:
        window.blit(window.getTexture(Textures::SlowUpButton), 90.0, speedRect);
        break;

    case 2:
        window.blit(window.getTexture(Textures::NormalUpButton), 90.0, speedRect);
        break;

    case 3:
        window.blit(window.getTexture(Textures::FastUpButton), 90.0, speedRect);
        break;

    default:
        break;
    }
}

Node* SetStepNode::use() {
    float distance = SDL_atof(distanceTyper.getString());
    if (distance > 0) {
        device.sendStepUp(speed, distance);
    } else {
        device.sendStepDown(speed, -distance);
    }
    logger.additional("> Set step by %f", distance);
    return this;
}

Node* SetStepNode::handlReachPos() const {
    logger.additional("> Get to target (step node)");
    return nextNode;
}

void SetStepNode::save(SDL_IOStream* _fout) {
    SDL_IOprintf(_fout, "e%c%s\n", speed+'0', distanceTyper.getString());
}
