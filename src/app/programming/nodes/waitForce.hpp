/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for wait, until force exceed or loose target value
class WaitForceNode : public Node {
private:
    bool mode;  // 0: as exceed, 1: as loose

    GUI::StaticText text;
    GUI::TextButton moreButton;
    GUI::TextButton lessButton;
    GUI::TypeBox forceTyper;

public:
    WaitForceNode(const Window& window, float X, float Y, char type = '0', const char* force = "10");

    // Programming
    Node* copy() override;
    void move(float X, float Y) override;
    void checkOff(const Mouse mouse) override;
    GUI::Code click(const Mouse mouse) override;
    void unclick() override;
    bool type(SDL_Keycode code) override;
    bool writeString(const char* str) override;
    void update(float mouseX) override;
    void blit() const override;

    // Execution
    Node* use() override;
    Node* handleReachForce() const override;
    void save(SDL_IOStream* ofstream) override;
};
