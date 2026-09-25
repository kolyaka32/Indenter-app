/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"

// Node for set force graph null
class SetNullNode : public Node {
private:
    int type;  // 0: as avarage, 1: as last

    GUI::StaticText text;
    GUI::StaticText avarButton;
    GUI::RectBackplate avarButtonRect;
    GUI::StaticText lastButton;
    GUI::RectBackplate lastButtonRect;

public:
    SetNullNode(const Window &window, float X, float Y, char type = '0');

    // Programming
    GUI::Code click(const Mouse mouse) override;
    Node* copy() override;
    void move(float X, float Y) override;
    void blit() const override;

    // Execution
    Node* use() override;
    void save(SDL_IOStream* ofstream) override;
};
