/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "setTarget.hpp"
#include "../../device.hpp"


SetTargetNode::SetTargetNode(const Window& _window, float _X, float _Y)
: Node(_window, _X, _Y, Textures::BlockLongAction),
text(_window, _X-rect.w/(2*window.getWidth())+0.005, _Y, {"Move to", "Двигаться к"},
    Height::Main, WHITE, GUI::Aligment::Left),
connectTarget(_window, _X+0.023, _Y),
positionNode(nullptr) {}

GUI::Code SetTargetNode::click(const Mouse _mouse) {
    if (in(_mouse)) {
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
    connectTarget.move(_X, _Y);
    if (positionNode) {
        positionNode->move(_X, _Y);
    }
}

void SetTargetNode::blit() const {
    Node::blit();
    text.blit();
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
            device.sendMoveToPos(1, node->getPos());  // ! Add speeds
            return this;
        }
    }
    // return stop in any other case
    return nullptr;
}

Node* SetTargetNode::handlReachPos() const {
    // Get at target - move to next node
    return nextNode;
}

void SetTargetNode::save(SDL_IOStream* _fout) {
    if (positionNode) {
        SDL_IOprintf(_fout, "t%d\n", positionNode->getNumber());
    } else {
        SDL_IOprintf(_fout, "t0\n");
    }
}
