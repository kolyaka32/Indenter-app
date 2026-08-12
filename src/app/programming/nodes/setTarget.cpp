/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setTarget.hpp"
#include "../../device.hpp"
#include "../programMenu.hpp"


SetTargetNode::SetTargetNode(const Window& _window, float _X, float _Y, char _speed)
: Node(_window, _X, _Y, Textures::BlockLongAction),
positionNode(nullptr),
speed(_speed - '0'),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y,
    {"Move       to", "Двигаться       к"}, GUI::Aligment::Left),
speedRect{(_X + (LanguagedText::getLanguage()==Language::Russian ? -0.002f : -0.027f))*window.getWidth(),
    _Y*window.getHeight()-18.0f, 32.0, 32.0},
connectTarget(_window, _X + (LanguagedText::getLanguage()==Language::Russian ? 0.039f : 0.019f), _Y) {}

GUI::Code SetTargetNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
        if (_mouse.in(speedRect)) {
            speed = (speed) % 3 + 1;
            return GUI::Button2;
        }
        if (positionNode && positionNode->in(_mouse)) {
            return GUI::Activate;
        }
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

SubNode* SetTargetNode::takeSubNode() {
    SubNode* temp = positionNode;
    positionNode = nullptr;
    return temp;
}

void SetTargetNode::disconnect(const Node* _node) {
    // Check, if delete current node
    if (_node == this) {
        // Check, if has position
        if (positionNode) {
            delete positionNode;
            positionNode = nullptr;
        }
        return;
    }

    // Check, if delete argument node
    if (positionNode) {
        if (positionNode->getSource() == _node) {
            delete positionNode;
            positionNode = nullptr;
        }
    }
}

void SetTargetNode::connectSubNode(SubNode* _subNode) {
    // Check, if already has node
    if (positionNode) {
        // Remove previous
        delete positionNode;
    }
    // Set new node
    positionNode = (PosSubNode*)_subNode;
    // Move it to place
    _subNode->moveTo(&connectTarget);
}

bool SetTargetNode::tryConnectSubNode(SubNode* _subNode) {
    // Check, if near
    if (connectTarget.isNear(_subNode)) {
        connectSubNode(_subNode);
        return true;
    }
    return false;
}

Node* SetTargetNode::copy() {
    return new SetTargetNode{window, (rect.x + rect.w / 2) / window.getWidth(),
        (rect.y + rect.h / 2) / window.getHeight()};
}

void SetTargetNode::move(float _X, float _Y) {
    Node::move(_X, _Y);
    text.move(_X, _Y);
    speedRect.x += _X * window.getWidth();
    speedRect.y += _Y * window.getHeight();
    connectTarget.move(_X, _Y);
    if (positionNode) {
        positionNode->move(_X, _Y);
    }
}

void SetTargetNode::blit() const {
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
    // Check, what node to draw
    if (positionNode) {
        positionNode->blit();
    } else {
        connectTarget.blit();
    }
}

Node* SetTargetNode::use() {
    // Check if position avaliable
    if (positionNode) {
        GetPosNode* node = (GetPosNode*)positionNode->getSource();
        if (node && node->isLegimate()) {
            // Send move
            device.sendMoveToPos(speed, node->getPos());
            logger.additional("Start move to %d", node->getPos());
            return this;
        }
    }
    // return stop in any other case
    return nullptr;
}

Node* SetTargetNode::handlReachPos() const {
    logger.additional("> Get to target (position node)");
    return nextNode;
}

void SetTargetNode::save(SDL_IOStream* _fout) {
    saveMain(_fout, 't');

    // Find subNode source
    unsigned pos = 0;
    if (positionNode) {
        pos = ProgramMenu::program.getNodePos(positionNode->getSource());
    }
    // Write speed and pos
    SDL_IOprintf(_fout, " %c %d", speed+'0', pos);
}
