/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for move by setted [distance]
class SetStepNode : public Node {
private:
    GUI::StaticText text;
    GUI::TypeBox<4> distanceTyper;

public:
    SetStepNode(const Window& window, float X, float Y, const char* val = "0");

    // Interaction
    void checkOff(const Mouse mouse) override;
    GUI::Code click(const Mouse mouse) override;
    void unclick() override;
    void type(SDL_Keycode code) override;
    void writeString(const char* str) override;
    void update(float mouseX) override;
    void blit() const override;

    // Programming
    Node* copy() override;
    void move(float X, float Y) override;

    // Execution
    Node* use() override;
    Node* handlReachPos() const override;
    void save(SDL_IOStream* ofstream) override;
};
