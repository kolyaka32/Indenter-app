/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "nodeSelector.hpp"


NodeSelector::NodeSelector(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H, 2.0),
nodes {
    {},  // SetSpeed
    {},  // WaitNone
    {},  // WaitPosition
    {},  // WaitForce
    {},  // Start
    {},  // WhileStart
    {},  // WhileEnd
    {},  // LoopStart
    {},  // LoopEnd
} {}

Node* NodeSelector::click(const Mouse _mouse) {

}

bool NodeSelector::unclick(const Mouse _mouse) {

}

void NodeSelector::update() {

}

void NodeSelector::blit() const {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i].blit();
    }
}
