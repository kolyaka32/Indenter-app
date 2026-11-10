/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setMove.hpp"
#include "../../device.hpp"


SetMoveNode::SetMoveNode(const Window& _window, float _X, float _Y, char _speed, char _direction)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, {"Move", "Двигаться"}, {_X-rect.w/(2*window.getWidth())+0.005f, _Y, .horAli=GUI::Left}),
speed(getSpeed(_speed)),
direction(getDirection(_direction)) {
    speedRect = {(_X + (LanguagedText::getLanguage()==Language::Russian ? 0.014f : -0.011f))*
        window.getWidth(), _Y*window.getHeight()-18.0f, 32.0, 32.0};
    directionRect = {(_X + (LanguagedText::getLanguage()==Language::Russian ? 0.030f : 0.005f))*
        window.getWidth(), _Y*window.getHeight()-18.0f, 32.0, 32.0};
}

Node* SetMoveNode::copy() {
    return new SetMoveNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), getLetter(speed), getLetter(direction)};
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
            getNextSpeed(speed);
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
    blitSpeed(speed, speedRect);
    blitDirection(direction, directionRect);
}

Node* SetMoveNode::use() {
    if (direction) {
        device.sendMoveUp(getSendSpeed(speed));
        logger.additional("> Start movement up %d", speed);
    } else {
        device.sendMoveDown(getSendSpeed(speed));
        logger.additional("> Start movement down %d", speed);
    }
    return nextNode;
}

void SetMoveNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, 'm');
    SDL_IOprintf(_fout, " %c %c", getLetter(speed), getLetter(direction));
}
