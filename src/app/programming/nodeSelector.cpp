/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "nodeSelector.hpp"


NodeSelector::NodeSelector(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H, 2.0) {
    // Creating all nodes
    addNode<Node>(_window, _X, _Y, _H);  // Start
    addNode<Node>(_window, _X, _Y, _H);  // WhileStart
    addNode<Node>(_window, _X, _Y, _H);  // LoopStart
    addNode<Node>(_window, _X, _Y, _H);  // SetSpeed
    addNode<Node>(_window, _X, _Y, _H);  // Stop
    addNode<Node>(_window, _X, _Y, _H);  // WaitNone
    addNode<Node>(_window, _X, _Y, _H);  // WaitPosition
    addNode<Node>(_window, _X, _Y, _H);  // WaitForce
}

NodeSelector::~NodeSelector() {
    for (int i=0; i < nodes.size(); ++i) {
        delete nodes[i];
    }
}

Node* NodeSelector::click(const Mouse _mouse) {
    return nullptr;
}

bool NodeSelector::unclick(const Mouse _mouse) {
    return false;
}

void NodeSelector::update() {

}

void NodeSelector::blit() const {
    background.blit();
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->blit();
    }
}
