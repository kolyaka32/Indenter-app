/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "subNode.hpp"
#include "../nodes/node.hpp"


// Sub node for trasfer absolute position (from getPos to setTarget)
class PosSubNode : public SubNode {
private:
    Node* srcNode;

    GUI::StaticText text;

public:
    PosSubNode(const Window& window, float X, float Y, Node* sourceNode, int number);

    // Programming
    SubNode* copy() override;
    void move(float X, float Y) override;
    void blit() const override;
};
