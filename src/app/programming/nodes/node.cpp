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

void Node::move(float _X, float _Y) {
    // Move current node
    TextureTemplate::move(_X, _Y);
    // Move arrow
    arrowRect.x += _X * window.getWidth();
    arrowRect.y += _Y * window.getHeight();
}

Node* Node::getNext() const {
    return nextNode;
}

bool Node::connectUpTo(Node* _target) {
    // Check, if himself
    if (_target == this) {
        return false;
    }
    // Try connect with upper pin
    if (_target->nextNode == nullptr) {
        // Check, if near
        SDL_FPoint current = getUpperPin();
        SDL_FPoint targetPin = _target->getBottomPin();
        float delta = sqr(current.x - targetPin.x) + sqr(current.y - targetPin.y);
        if (delta < connectDistance) {
            // Exchanging pointers
            previousNode = _target;
            _target->nextNode = this;
            // Move this and connected nodes
            float dx = (targetPin.x - current.x) / window.getWidth();
            float dy = (targetPin.y - current.y) / window.getHeight();
            // Move all connected nodes
            Node* moveNode = this;
            while (moveNode) {
                moveNode->move(dx, dy);
                moveNode = moveNode->nextNode;
            }
            return true;
        }
    }
    return false;
}

bool Node::connectBottomTo(Node* _target) {
    // Check, if himself
    if (_target == this) {
        return false;
    }
    // Try connect with down pin
    if (_target->previousNode == nullptr) {
        // Check, if near
        SDL_FPoint current = getBottomPin();
        SDL_FPoint targetPin = _target->getUpperPin();
        float delta = sqr(current.x - targetPin.x) + sqr(current.y - targetPin.y);
        if (delta < connectDistance) {
            // Exchanging pointers
            nextNode = _target;
            _target->previousNode = this;
            // Move this and connected nodes
            float dx = (targetPin.x - current.x) / window.getWidth();
            float dy = (targetPin.y - current.y) / window.getHeight();
            // Move this and connected nodes in reverse order
            Node* moveNode = this;
            while (moveNode) {
                moveNode->move(dx, dy);
                moveNode = moveNode->previousNode;
            }
            return true;
        }
    }
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
    return SDL_FPoint{rect.x, rect.y + rect.h};  // ! small correction required for pin
}

SDL_FPoint Node::getUpperPin() const {
    return SDL_FPoint{rect.x, rect.y};
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
