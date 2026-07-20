/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for set movement in selected [direction] with selected [speed]
class SetMoveNode : public Node {
private:
    bool moveUp;
    bool moveIdle;

    GUI::StaticText text;

public:
    SetMoveNode(const Window& window, float X, float Y);

    Node* use() override;
    Node* copy() const override;
    //void disconnect(const Node* node) override;
    //bool isDeletable() const override;
    void move(float X, float Y) override;
    void blit() const override;

    // Handles
    Node* handleGetPos() override;
    Node* handlReachPos() const override;
    Node* handleReachForce() const override;
};
