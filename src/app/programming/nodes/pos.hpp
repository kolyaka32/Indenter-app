/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Sub node for trasfer absolute position (from getPos to setTarget)
class PosSubNode : public Node {
private:
    int number;
    Node* srcNode;

    GUI::StaticText text;

public:
    PosSubNode(const Window& window, float X, float Y, Node* sourceNode, int number);

    // Programming
    Node* copy() override;
    void move(float X, float Y) override;
    void blit() const override;
};
