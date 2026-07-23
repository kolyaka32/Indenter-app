/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "pos.hpp"


// Node for get and save current [position]
class GetPosNode : public Node {
private:
    // Useful data
    int position;
    bool legimate;  // Is position can be used
    static int number;

    // Graphical part
    GUI::StaticText text;
    // Saved position as part of interface for interaction
    PosSubNode posSubNode;

public:
    GetPosNode(const Window& window, float X, float Y);

    // Programming
    GUI::Code click(const Mouse mouse) override;
    Node* copy() override;
    void move(float X, float Y) override;
    Node* takeSubNode() override;
    void blit() const override;

    // Execution
    void reset() override;
    Node* use() override;
    Node* handleGetPos(int pos) override;
    void save(SDL_IOStream* ofstream) override;

    static void resetCounter();
};
