/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "node.hpp"


Node::Node(const Window& _window, float _X, float _Y, Textures _texture)
: TextureTemplate(_window, _window.getTexture(_texture)),
arrowTexture(window.getTexture(Textures::UpButton)),
previousNode(nullptr),
nextNode(nullptr) {
    // Update pos
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = _X * window.getWidth() - rect.w/2;
    rect.y = _Y * window.getHeight() - rect.h/2;
    // Update arrow rect
    arrowRect.w = arrowTexture->w;
    arrowRect.h = arrowTexture->h;
    arrowRect.x = (_X - 0.05) * window.getWidth() - arrowRect.w/2;
    arrowRect.y = _Y * window.getHeight() - arrowRect.h/2;
}

bool Node::click(const Mouse mouse) {
    return false;
}

void Node::moveNode(float _X, float _Y) {
    // Move current node
    TextureTemplate::move(_X, _Y);
    // Move arrow
    arrowRect.x += _X * window.getWidth();
    arrowRect.y += _Y * window.getHeight();
    // Try move next nodes
    if (nextNode) {
        nextNode->moveNode(_X, _Y);
    }
}

Node* Node::getNext() const {
    return nextNode;
}

bool Node::connectTo(Node* _node) {
    // Check, if try connect with upper pin

    // !
    /*if (previousNode) {
        // Check, if near
        SDL_FPoint upperPoint = 
        float delta = sqr(rect.x - _node->rect.x) + sqr(rect.y + rect.h - _node->rect.y);
        if (delta < 20.0) {
            return true;
        }
        
    }
    // Check, if try connect with down pin
    if (nextNode == nullptr) {
        // Check, if near
        float delta = sqr(rect.x - _node->rect.x) + sqr(rect.y + rect.h - _node->rect.y);
        if (delta < 20.0) {
            // Add link to both node
            nextNode = _node;
            _node->previousNode = this;
            // Correcting placement of next node
            _node->rect.x = rect.x;
            _node->rect.y = rect.y + rect.h;
            return true;
        }
    }*/
    return false;
}

Node* Node::take(const Mouse _mouse) {
    if (in(_mouse)) {
        // Disconnect previous node
        if (previousNode) {
            previousNode->nextNode = nullptr;
            previousNode = nullptr;
        }
        return this;
    }
    return nullptr;
}

void Node::update() {

}

Node* Node::use() {
    return nullptr;
}

Node* Node::copy() const {
    return new Node{window, rect.x/window.getWidth(), rect.y/window.getHeight(), Textures::BlockLoopStart};
}

SDL_FPoint Node::getBottomPin() const {
    return SDL_FPoint{rect.x, rect.y + rect.h};
}


void Node::disconnect(const Node* _node) {
    // Don't do anything with it
}

bool Node::isDeletable() const {
    return true;
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

void Node::blitCurrent() const {
    window.blit(arrowTexture, arrowRect);
}
