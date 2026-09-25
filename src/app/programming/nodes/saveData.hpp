/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"

// Node for save collected data
class SaveDataNode : public Node {
private:
    GUI::StaticText text;
    GUI::TypeBox nameTyper;

public:
    SaveDataNode(const Window &window, float X, float Y, const char* val = "result");

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
    void save(SDL_IOStream* ofstream) override;
};
