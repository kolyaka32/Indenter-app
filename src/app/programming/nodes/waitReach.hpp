/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "getPos.hpp"


// Node for wait, until force exceed target
class WaitReachNode : public Node {
private:
    // Data-8
    GUI::StaticText text;

public:
    WaitReachNode(const Window& window, float X, float Y);

    // GUI::Code click(const Mouse mouse) override;
    Node *copy() const override;
    void move(float X, float Y) override;
    void blit() const override;
    // void save(SDL_IOStream* ofstream) const override;

    // // Handles
    Node *use() override;
};
