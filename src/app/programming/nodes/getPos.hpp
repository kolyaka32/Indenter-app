/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for get and save current [position]
class GetPosNode : public Node {
private:
    // Useful data
    int position;
    bool legimate;  // Is position can be used

    // Graphical part
    GUI::StaticText text;

public:
    GetPosNode(const Window& window, float X, float Y);

    void reset() override;
    // GUI::Code click(const Mouse mouse) override;
    Node *copy() override;
    void move(float X, float Y) override;
    void blit() const override;
    
    // Handles
    Node *use() override;
    Node* handleGetPos(int pos) override;
    void save(SDL_IOStream* ofstream) override;
};
