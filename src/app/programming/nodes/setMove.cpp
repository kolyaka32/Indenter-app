/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setMove.hpp"
#include "../../device.hpp"


SetMoveNode::SetMoveNode(const Window& _window, float _X, float _Y, char _speed, char _direction)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Move", "Двигаться"},
    Height::Main, WHITE, GUI::Aligment::Left),
speed(_speed - '0'),
direction(_direction - '0') {
    speedRect = {(_X + (LanguagedText::getLanguage()==Language::Russian ? 0.014f : -0.011f))*
        window.getWidth(), _Y*window.getHeight()-18.0f, 32.0, 32.0};
    directionRect = {(_X + (LanguagedText::getLanguage()==Language::Russian ? 0.030f : 0.005f))*
        window.getWidth(), _Y*window.getHeight()-18.0f, 32.0, 32.0};
}

Node* SetMoveNode::copy() {
    return new SetMoveNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), char(speed + '0'), char(direction + '0')};
}

void SetMoveNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    directionRect.x += _X * window.getWidth();
    directionRect.y += _Y * window.getHeight();
    speedRect.x += _X * window.getWidth();
    speedRect.y += _Y * window.getHeight();
}

GUI::Code SetMoveNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
        if (_mouse.in(speedRect)) {
            speed = (speed) % 3 + 1;
            return GUI::Button2;
        }
        if (_mouse.in(directionRect)) {
            direction ^= true;
            return GUI::Button1;
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

void SetMoveNode::blit() const {
    Node::blit();
    text.blit();
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
    // Direction
    if (direction) {
        window.blit(window.getTexture(Textures::SlowDownButton), directionRect);
    } else {
        window.blit(window.getTexture(Textures::SlowUpButton), directionRect);
    }
}

Node* SetMoveNode::use() {
    if (direction) {
        device.sendMoveUp(speed);
        logger.additional("> Start movement up %d", speed);
    } else {
        device.sendMoveDown(speed);
        logger.additional("> Start movement down %d", speed);
    }
    return nextNode;
}

void SetMoveNode::save(SDL_IOStream* _fout) {
    SDL_IOprintf(_fout, "m%c%c\n", speed+'0', direction+'0');
}
