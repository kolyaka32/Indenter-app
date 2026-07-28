/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "getPos.hpp"


// Node for absolute movement to stored 
class SetTargetNode : public Node {
private:
    Uint16 speed;  // Speeds: slow=1, normal=2, fast=3
    PosSubNode* positionNode;

    // Graphical part
    GUI::StaticText text;
    SDL_FRect speedRect;
    SubNode connectTarget;  // Place to connect posSubNode

public:
    SetTargetNode(const Window& window, float X, float Y, char speed = '1');

    // Programming
    GUI::Code click(const Mouse mouse) override;
    SubNode* takeSubNode() override;
    void disconnect(const Node* node) override;
    void connectSubNode(SubNode* subNode) override;
    bool tryConnectSubNode(SubNode* subNode) override;
    Node* copy() override;
    void move(float X, float Y) override;
    void blit() const override;

    // Execution
    Node* use() override;
    Node* handlReachPos() const override;
    void save(SDL_IOStream* ofstream) override;
};
