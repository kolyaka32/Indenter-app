/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for set movement in selected [direction] with selected [speed]
class SetMoveNode : public Node {
private:
    Uint16 speed;  // Speeds: slow=1, normal=2, fast=3
    bool direction;  // false for down and true for up

    GUI::StaticText text;
    SDL_FRect directionRect;
    SDL_FRect speedRect;

public:
    SetMoveNode(const Window& window, float X, float Y, char speed = '1', char direction = '0');

    GUI::Code click(const Mouse mouse) override;
    Node* copy() override;
    void move(float X, float Y) override;
    void blit() const override;

    // Execution
    Node* use() override;
    void save(SDL_IOStream* ofstream) override;
};
