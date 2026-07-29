/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "nodeSelector.hpp"


NodeSelector::NodeSelector(const Window& _window, float _X, float _Y, float _W, float _H) noexcept
: Template(_window),
nodes{},
background(_window, _X, _Y, _W, _H, 2.0) {
    // Creating all nodes
    count = 0;
    addNode<SetStopNode>(_X, _Y, _H);
    addNode<SetMoveNode>(_X, _Y, _H);
    addNode<SetStepNode>(_X, _Y, _H);
    addNode<SetTargetNode>(_X, _Y, _H);
    addNode<GetPosNode>(_X, _Y, _H);
    addNode<WaitReachNode>(_X, _Y, _H);
    addNode<WaitLoseNode>(_X, _Y, _H);
    addNode<HaltNode>(_X, _Y, _H);
    //addNode<Node>(_X, _Y, _H);  // WhileStart
    //addNode<Node>(_X, _Y, _H);  // LoopStart
}

NodeSelector::~NodeSelector() {
    for (int i=0; i < nodes.size(); ++i) {
        delete nodes[i];
    }
}

bool NodeSelector::in(const Mouse _mouse) const {
    return background.in(_mouse);
}

void NodeSelector::checkOff(const Mouse _mouse) {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->checkOff(_mouse);
    }
}

Node* NodeSelector::click(const Mouse _mouse) {
    // Check on stop interaction
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->checkOff(_mouse);
    }
    // Check for all nodes
    for (int i=0; i < nodes.size(); ++i) {
        if (GUI::Code code = nodes[i]->click(_mouse)) {
            // Check on action in this block
            if (code == GUI::Some) {
                // Create new node for interaction
                logger.additional("Create new node at %d", i);
                return nodes[i]->copy();
            }
        }
    }
    return nullptr;
}

void NodeSelector::unclick() {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->unclick();
    }
}

void NodeSelector::type(SDL_Keycode _code) {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->type(_code);
    }
}

void NodeSelector::writeString(const char* _str) {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->writeString(_str);
    }
}

void NodeSelector::update(const Mouse _mouse) {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->update(_mouse.getX());
    }
}

void NodeSelector::blit() const {
    background.blit();
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->blit();
    }
}
