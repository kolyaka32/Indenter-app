/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setNull.hpp"
#include "../../output/collectedData.hpp"


SetNullNode::SetNullNode(const Window& _window, float _X, float _Y, char _type)
: Node(_window, _X, _Y, Textures::BlockLongAction),
type(_type - '0'),
text(_window, {"Set null as", "Уст. ноль как"}, {_X-rect.w/(2*window.getWidth())+0.005f, _Y, .horAli=GUI::Left}),
avarButton(_window, {"avarage", "среднее"}, {_X+0.014f, _Y, .horAli=GUI::Left, .textColor=BLACK}),
avarButtonRect(_window, _X+0.041f, _Y, 0.06, 0.03, 1.0, WHITE),
lastButton(_window, {"last", "последнее"}, {_X+0.014f, _Y, .horAli=GUI::Left, .textColor=BLACK}),
lastButtonRect(_window, _X+0.041f, _Y, 0.06, 0.03, 1.0, WHITE) {}

GUI::Code SetNullNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
        if (type) {
            if (lastButton.in(_mouse)) {
                type = 0;
                return GUI::Button1;
            }
        } else {
            if (avarButton.in(_mouse)) {
                type = 1;
                return GUI::Button1;
            }
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

Node* SetNullNode::copy() {
    return new SetNullNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), char(type+'0')};
}

void SetNullNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    avarButton.move(_X, _Y);
    lastButton.move(_X, _Y);
}

void SetNullNode::blit() const {
    Node::blit();
    text.blit();
    if (type) {
        avarButtonRect.blit();
        lastButton.blit();
    } else {
        lastButtonRect.blit();
        avarButton.blit();
    }
}

Node* SetNullNode::use() {
    if (type) {
        collectedData.setForceNullAsAvar();
    } else {
        collectedData.setForceNullAsLast();
    }
    logger.additional("> Set graph null");
    return nextNode;
}

void SetNullNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, 'u');
    SDL_IOprintf(_fout, " %c", type+'0');
}
