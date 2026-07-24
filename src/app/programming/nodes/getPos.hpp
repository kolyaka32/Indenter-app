/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"
#include "../subNodes/pos.hpp"


// Node for get and save current [position]
class GetPosNode : public Node {
private:
    // Useful data
    int position;   // Saved position
    bool legimate;  // Is position can be used
    static int counter;  // Global counter for proper naming

    // Graphical part
    GUI::StaticText text;
    // Saved position as part of interface for interaction
    PosSubNode posSubNode;

public:
    // Normal create with new number
    GetPosNode(const Window& window, float X, float Y);

    // Programming
    GUI::Code click(const Mouse mouse) override;
    Node* copy() override;
    void move(float X, float Y) override;
    SubNode* takeSubNode() override;
    void blit() const override;
    // Exclusive for that node
    bool isLegimate() const;
    int getPos() const;

    // Execution
    void reset() override;
    Node* use() override;
    Node* handleGetPos(int pos) override;
    void save(SDL_IOStream* ofstream) override;

    static void resetCounter();
};
