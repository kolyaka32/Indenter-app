/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for move by setted [distance]
class SetStepNode : public Node {
private:
    Uint16 speed;  // Speeds: slow=1, normal=2, fast=3

    GUI::StaticText text;
    SDL_FRect speedRect;
    GUI::TypeBox<4> distanceTyper;

public:
    SetStepNode(const Window& window, float X, float Y, char speed = '1', const char* val = "0");

    // Interaction
    Node* copy() override;
    void move(float X, float Y) override;
    void checkOff(const Mouse mouse) override;
    GUI::Code click(const Mouse mouse) override;
    void unclick() override;
    void type(SDL_Keycode code) override;
    void writeString(const char* str) override;
    void update(float mouseX) override;
    void blit() const override;

    // Execution
    Node* use() override;
    Node* handlReachPos() const override;
    void save(SDL_IOStream* ofstream) override;
};
