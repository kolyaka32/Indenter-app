/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "getPos.hpp"


// Node for absolute movement to stored 
class SetTargetNode : public Node {
private:
    PosSubNode* positionNode;

    // Graphica part
    GUI::StaticText text;
    // Place to connect posSubNode
    SubNode connectTarget;

public:
    SetTargetNode(const Window& window, float X, float Y);

    // Programming
    Node* copy() override;
    void move(float X, float Y) override;
    void blit() const override;

    // Execution
    Node* use() override;
    Node* handlReachPos() const override;
    void connectSubNode(SubNode* subNode) override;
    bool tryConnectSubNode(SubNode* subNode) override;
    void save(SDL_IOStream* ofstream) override;
};
