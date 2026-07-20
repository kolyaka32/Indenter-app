/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "nodeSelector.hpp"


NodeSelector::NodeSelector(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
nodes{},
background(_window, _X, _Y, _W, _H, 2.0) {
    // Creating all nodes
    count = 0;
    addNode<StopNode>(_X, _Y, _H);
    addNode<SetMoveNode>(_X, _Y, _H);
    addNode<SetStepNode>(_X, _Y, _H);
    addNode<SetTargetNode>(_X, _Y, _H);
    addNode<GetPosNode>(_X, _Y, _H);
    addNode<WaitReachNode>(_X, _Y, _H);
    addNode<WaitLoseNode>(_X, _Y, _H);
    //addNode<Node>(_X, _Y, _H);  // WhileStart
    //addNode<Node>(_X, _Y, _H);  // LoopStart
}

NodeSelector::~NodeSelector() {
    for (int i=0; i < nodes.size(); ++i) {
        delete nodes[i];
    }
}

Node* NodeSelector::click(const Mouse _mouse) {
    // Check for all nodes
    for (int i=0; i < nodes.size(); ++i) {
        if (nodes[i]->in(_mouse)) {
            // Create new node for interaction
            logger.additional("Create new node at %d", i);
            return nodes[i]->copy();
        }
    }
    return nullptr;
}

bool NodeSelector::unclick(const Mouse _mouse) {
    return background.in(_mouse);
}

void NodeSelector::update() {

}

void NodeSelector::blit() const {
    background.blit();
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->blit();
    }
}
