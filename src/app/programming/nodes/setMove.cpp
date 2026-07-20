/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setMove.hpp"
#include "../../device.hpp"


SetMoveNode::SetMoveNode(const Window& _window, float _X, float _Y, bool _moveUp, bool _moveIdle)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, _X-0.04, _Y, {"Move", "Двигаться"}, Height::Main, WHITE, GUI::Aligment::Left),
moveUp(_moveUp),
moveIdle(_moveIdle) {
    directionRect = {(_X+0.018f)*window.getWidth(), _Y*window.getHeight()-15.0f, 30.0, 30.0};
    speedRect = {(_X+0.033f)*window.getWidth(), _Y*window.getHeight()-15.0f, 30.0, 30.0};
}

GUI::Code SetMoveNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
        if (_mouse.in(directionRect)) {
            moveUp ^= true;
            return GUI::Button1;
        }
        if (_mouse.in(speedRect)) {
            moveIdle ^= true;
            return GUI::Button2;
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

Node* SetMoveNode::use() {
    if (moveUp) {
        // Could be changed to set speed as argument
        if (moveIdle) {
            device.sendIdleUp();
        } else {
            device.sendMoveUp();
        }
    } else {
        if (moveIdle) {
            device.sendIdleUp();
        } else {
            device.sendMoveUp();
        }
    }
    // Move to next node
    return nextNode;
}

Node* SetMoveNode::copy() const {
    return new SetMoveNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), moveUp, moveIdle};
}

void SetMoveNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    directionRect.x += _X * window.getWidth();
    directionRect.y += _Y * window.getHeight();
    speedRect.x += _X * window.getWidth();
    speedRect.y += _Y * window.getHeight();
}

void SetMoveNode::blit() const {
    Node::blit();
    text.blit();
    if (moveUp) {
        window.blit(window.getTexture(Textures::UpButton), directionRect);
    } else {
        window.blit(window.getTexture(Textures::DownButton), directionRect);
    }
    if (moveIdle) {
        window.blit(window.getTexture(Textures::UpButton), 90.0, speedRect);
    } else {
        window.blit(window.getTexture(Textures::FastUpButton), 90.0, speedRect);
    }
}

void SetMoveNode::save(SDL_IOStream* _fout) const {
    SDL_IOprintf(_fout, "m%c%c\n", moveUp+'c', moveIdle+'c');
}
