/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "node.hpp"


Node::Node(const Window& _window, float _X, float _Y, Textures _texture)
: TextureTemplate(_window, _window.getTexture(_texture)),
previousNode(nullptr),
nextNode(nullptr) {
    // Update pos
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = _X * window.getWidth() - rect.w/2;
    rect.y = _Y * window.getHeight() - rect.h/2;
}

bool Node::click(const Mouse mouse) {
    return false;
}

void Node::moveNode(float _X, float _Y) {
    // Move current node
    TextureTemplate::move(_X, _Y);
    // Move next nodes
    nextNode->moveNode(_X, _Y);
}

void Node::update() {

}

Node* Node::use() {
    return this;
}

Node* Node::copy() const {
    return new Node{window, rect.x, rect.y, Textures::BlockStart};
}

Node* Node::handleGetPos() {
    return nullptr;
}

Node* Node::handlReachPos() const {
    return nullptr;
}

Node* Node::handleReachForce() const {
    return nullptr;
}

void Node::blit() const  {
    window.blit(texture, rect);
}
