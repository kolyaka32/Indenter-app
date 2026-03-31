/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "../serial/serial.hpp"



class CurrentPort : GUI::Template {
private:
    static bool openned;
    static int selected;

    // Variants, that currently shown
    static std::array<bool, 4> avaliableTexts;

    // Graphic part
    const float arrow = 0.02;
    const float height;
    SDL_FRect background;
    GUI::StaticText texts[5];

public:
    CurrentPort(const Window& window, float X, float Y, float W, float H);
    ~CurrentPort();
    void reset();
    void update();
    bool click(const Mouse mouse);  // Return number, if select any
    void blit() const override;

    // Working straight with serial
    void selectPort(int port);
    void resetPort();
};
