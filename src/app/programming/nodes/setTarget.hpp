/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "getPos.hpp"


// Node for absolute movement to stored 
class SetTargetNode : public Node {
private:
    GetPosNode* positionNode;
    GUI::StaticText text;
    // ! Required destination node source

public:
    SetTargetNode(const Window& window, float X, float Y);

    // Programming
    Node* copy() override;
    void move(float X, float Y) override;
    void blit() const override;

    // Execution
    Node* use() override;
    Node* handlReachPos() const override;
    void save(SDL_IOStream* ofstream) override;
};
