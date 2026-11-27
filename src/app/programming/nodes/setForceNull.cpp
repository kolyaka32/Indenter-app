/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setForceNull.hpp"
#include "../../output/collectedData.hpp"


SetForceNullNode::SetForceNullNode(const Window& _window, float _X, float _Y, char _type)
: Node(_window, _X, _Y, Textures::BlockLongAction),
type(_type - '0'),
posX(_X + (LanguagedText::getLanguage()==Language::Russian ? 0.014f : 0.002f)),
text(_window, {"Set null as", "Уст. ноль как"}, {_X-rect.w/2/window.getWidth()+0.005f, _Y, .horAli=GUI::Left}),
avarButton(_window, {"avarage", "среднее"}, {posX, _Y, .horAli=GUI::Left, .textColor=BLACK}),
avarButtonRect(_window, posX+0.027f, _Y, 0.06, 0.03, 1.0, WHITE),
lastButton(_window, {"last", "последнее"}, {posX, _Y, .horAli=GUI::Left, .textColor=BLACK}),
lastButtonRect(_window, posX+0.027f, _Y, 0.06, 0.03, 1.0, WHITE) {}

GUI::Code SetForceNullNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
        if (type) {
            if (lastButtonRect.in(_mouse)) {
                type = 0;
                return GUI::Button1;
            }
        } else {
            if (avarButtonRect.in(_mouse)) {
                type = 1;
                return GUI::Button1;
            }
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

Node* SetForceNullNode::copy() {
    return new SetForceNullNode{window, (rect.x+rect.w/2)/window.getWidth(),
        (rect.y+rect.h/2)/window.getHeight(), char(type+'0')};
}

void SetForceNullNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    avarButton.move(_X, _Y);
    avarButtonRect.move(_X, _Y);
    lastButton.move(_X, _Y);
    lastButtonRect.move(_X, _Y);
}

void SetForceNullNode::blit() const {
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

Node* SetForceNullNode::use() {
    if (type) {
        collectedData.setForceNullAsAvar();
    } else {
        collectedData.setForceNullAsLast();
    }
    logger.additional("> Set graph null");
    return nextNode;
}

void SetForceNullNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, NodeType::SetForceNull);
    SDL_IOprintf(_fout, " %c", type+'0');
}
