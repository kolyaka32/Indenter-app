/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "getPos.hpp"


// Node for wait, until force exceed target
class WaitReachNode : public Node {
private:
    GUI::StaticText text;
    GUI::TypeBox<6> forceTyper;

public:
    WaitReachNode(const Window& window, float X, float Y, const char* force = "10");

    // Programming
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
    Node* handleReachForce() const override;
    void save(SDL_IOStream* ofstream) override;
};
