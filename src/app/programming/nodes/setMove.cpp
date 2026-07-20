/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setMove.hpp"
#include "../../device.hpp"


SetMoveNode::SetMoveNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockAction),
text(_window, _X-0.03, _Y, {"Move", "Двигаться"}, Height::Main, WHITE, GUI::Aligment::Left) {
    moveUp = false;
    moveIdle = false;
}

GUI::Code SetMoveNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
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
        (rect.y+rect.h/2)/window.getHeight()};
}

void SetMoveNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
}

void SetMoveNode::blit() const {
    Node::blit();
    text.blit();
}
