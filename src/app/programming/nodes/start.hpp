/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node, from what program start execution
class StartNode : public Node {
private:
    GUI::StaticText text;

public:
    StartNode(const Window& window, float X, float Y);

    // Programming
    void move(float _X, float _Y) override;
    void disconnect(const Node* node) override;
    void blit() const override;

    // Execution
    void save(SDL_IOStream* ofstream) override;
};
