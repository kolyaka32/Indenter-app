/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "node.hpp"
#include "../programMenu.hpp"


Node::Node(const Window& _window, float _X, float _Y, Textures _texture,
    bool _connectableUp, bool _connectableDown, bool _delitable)
: TextureTemplate(_window, _window.getTexture(_texture)),
arrowTexture(window.getTexture(Textures::SlowUpButton)),
previousNode(nullptr),
nextNode(nullptr),
connectableUp(_connectableUp),
connectableDown(_connectableDown),
delitable(_delitable) {
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

void Node::disconnectPrevious() {
    if (previousNode) {
        previousNode->nextNode = nullptr;
        previousNode = nullptr;
    }
}

void Node::disconnectNext() {
    if (nextNode) {
        nextNode->previousNode = nullptr;
        nextNode = nullptr;
    }
}

SDL_FPoint Node::getBottomPin() const {
    return SDL_FPoint{rect.x, rect.y + rect.h - 7.0f};
}

SDL_FPoint Node::getUpperPin() const {
    return SDL_FPoint{rect.x, rect.y};
}

Node* Node::copy() {
    return new Node{window, rect.x/window.getWidth(), rect.y/window.getHeight(),
        Textures::BlockLoopStart, connectableUp, connectableDown, delitable};
}

void Node::move(float _X, float _Y) {
    // Move current node
    TextureTemplate::move(_X, _Y);
    // Move arrow
    arrowRect.x += _X * window.getWidth();
    arrowRect.y += _Y * window.getHeight();
}

void Node::checkOff(const Mouse _mouse) {}

GUI::Code Node::click(const Mouse _mouse) {
    if (in(_mouse)) {
        disconnectPrevious();
        return GUI::Some;
    }
    return GUI::None;
}

void Node::unclick() {}

bool Node::type(SDL_Keycode _code) {
    return false;
}

bool Node::writeString(const char* _str) {
    return false;
}

SubNode* Node::takeSubNode() {
    return nullptr;
}

void Node::update(float _mouseX) {}

void Node::blit() const  {
    window.blit(texture, rect);
}

void Node::blitCurrent() const {
    window.blit(arrowTexture, 90.0, arrowRect);
}

void Node::connectTopTo(Node* _target) {
    // Exchanging pointers
    previousNode = _target;
    _target->nextNode = this;
    // Move this and connected nodes
    SDL_FPoint current = getUpperPin();
    SDL_FPoint target = _target->getBottomPin();
    float dx = (target.x - current.x) / window.getWidth();
    float dy = (target.y - current.y) / window.getHeight();
    // Move all connected nodes
    Node* moveNode = this;
    while (moveNode) {
        moveNode->move(dx, dy);
        moveNode = moveNode->nextNode;
    }
}

void Node::connectBottomTo(Node* _target) {
    // Exchanging pointers
    nextNode = _target;
    _target->previousNode = this;
    // Move this and connected nodes
    SDL_FPoint current = getBottomPin();
    SDL_FPoint target = _target->getUpperPin();
    float dx = (target.x - current.x) / window.getWidth();
    float dy = (target.y - current.y) / window.getHeight();
    // Move this and connected nodes in reverse order
    Node* moveNode = this;
    while (moveNode) {
        moveNode->move(dx, dy);
        moveNode = moveNode->previousNode;
    }
}

void Node::connectSubNode(SubNode* _subNode) {}

bool Node::tryConnectTopTo(Node* _target) {
    // Check, if himself
    if (_target == this) {
        return false;
    }
    // Check on node rules
    if (!connectableUp || !_target->connectableDown) {
        return false;
    }
    // Check, if already has connection
    if (_target->nextNode) {
        return false;
    }
    // Check, if near
    SDL_FPoint current = getUpperPin();
    SDL_FPoint targetPin = _target->getBottomPin();
    if (sqr(current.x-targetPin.x) + sqr(current.y-targetPin.y) < connectDistance) {
        connectTopTo(_target);
        return true;
    }
    return false;
}

bool Node::tryConnectBottomTo(Node* _target) {
    // Check, if himself
    if (_target == this) {
        return false;
    }
    // Check on node rules
    if (!connectableDown || !_target->connectableUp) {
        return false;
    }
    // Check, if already has connection
    if (_target->previousNode) {
        return false;
    }
    // Check, if near
    SDL_FPoint current = getBottomPin();
    SDL_FPoint targetPin = _target->getUpperPin();
    if (sqr(current.x-targetPin.x) + sqr(current.y-targetPin.y) < connectDistance) {
        connectBottomTo(_target);
        return true;
    }
    return false;
}

bool Node::tryConnectSubNode(SubNode* _subNode) {
    return false;
}

bool Node::isDeletable() const {
    return delitable;
}

void Node::disconnect(const Node* _node) {}

Node* Node::getNext() const {
    return nextNode;
}

void Node::reset() {}

Node* Node::use() {
    return nullptr;
}

Node* Node::handleGetPos(int _pos) {
    return (Node*)this;
}

Node* Node::handlReachPos() const {
    return (Node*)this;
}

Node* Node::handleReachForce() const {
    return (Node*)this;
}

Node::Speed Node::getSpeed(char _letter) const {
    if (_letter > '0' && _letter <= '9') {
        return _letter - '0';
    }
    return 1;
}

char Node::getLetter(Speed _speed) const {
    return _speed + '0';
}

void Node::getNextSpeed(Speed& _current) const {
    _current = (_current) % 3 + 1;
}

Uint16 Node::getSendSpeed(Speed _speed) const {
    switch (_speed) {
    case 1:
        return 1;

    case 2:
        return 4;

    case 3:
        return 10;

    case 4:
        return 25;

    default:
        return 1;
    }
}

void Node::blitSpeed(Speed _speed, const SDL_FRect _rect) const {
    switch (_speed) {
    case 1:
        window.blit(window.getTexture(Textures::SlowUpButton), 90.0, _rect);
        break;

    case 2:
        window.blit(window.getTexture(Textures::NormalUpButton), 90.0, _rect);
        break;

    case 3:
        window.blit(window.getTexture(Textures::FastUpButton), 90.0, _rect);
        break;

    default:
        break;
    }
}

Node::Direction Node::getDirection(char _letter) const {
    if (_letter == '1') {
        return true;
    }
    return false;
}

char Node::getLetter(Direction _direction) const {
    return _direction + '0';
}

void Node::blitDirection(Direction _direction, const SDL_FRect _rect) const {
    if (_direction) {
        window.blit(window.getTexture(Textures::SlowDownButton), _rect);
    } else {
        window.blit(window.getTexture(Textures::SlowUpButton), _rect);
    }
}

void Node::saveMain(SDL_IOStream* _fout, char _type) {
    // Find position
    int x = (rect.x + rect.w/2)/window.getWidth() * 100;
    int y = (rect.y + rect.h/2)/window.getHeight() * 100;

    // Find next node
    unsigned next = ProgramMenu::program.getNodePos(nextNode);

    // Write all data
    SDL_IOprintf(_fout, "%c %02d %02d %03u", _type, x, y, next);
}

void Node::save(SDL_IOStream* _fout) {
    saveMain(_fout, 'n');
}
