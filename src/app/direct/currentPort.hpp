/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../GUI/interface.hpp"
#include "../../serial/comPort.hpp"


// Class for configuring com port to connect
class CurrentPort : GUI::Template {
 private:
    static bool openned;
    static int selected;

    // Graphic part
    const float arrow = 0.02;
    const float height;
    SDL_FRect background;
    SDL_FRect foreground;
    int count;
    GUI::HighlightedStaticText texts[5];

 protected:
    void showPort(int index);
    void hidePort(int index);
    int getPosition(const Mouse mouse);
    void connectToFirst();
    void maximize();
    void minimize();
    void moveSelectedUp();    // Move selected text to main position (for closing)
    void moveSelectedDown();  // Move selected text back to it postion (openning)

 public:
    CurrentPort(const Window& window, float X, float Y, float W, float H, float frameThickness) noexcept;
    void reset();

    bool click(const Mouse mouse);
    bool press(SDL_Keycode key);
    void update();
    void blit() const override;
};
