/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "../serial/comPort.hpp"


// Class for configuring com port to connect
class CurrentPort : GUI::Template {
 private:
    static bool openned;
    static int selected;

    // Array of avaliable com-ports
    static std::array<ComPort, 4> ports;  // Ports: 3, 4, 5, 6

    // Graphic part
    const float arrow = 0.02;
    const float height;
    SDL_FRect background;
    SDL_FRect foreground;
    int count;
    GUI::HighlightedStaticText texts[5];

 public:
    CurrentPort(const Window& window, float X, float Y, float W, float H, float frameThickness);
    void reset();
    void update();
    bool click(const Mouse mouse);  // Return number, if select any
    void blit() const override;
};
