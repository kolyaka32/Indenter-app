/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "currentPort.hpp"


// Class for interact with device and it state
class DeviceInterface : GUI::Template {
private:
    GUI::RoundedBackplate mainBackplate;
    GUI::HighlightedStaticText title;
    SDL_FRect separateRect;
    GUI::HighlightedStaticText portSelectText;
    CurrentPort serialPort;

    // Texts, showing current state
    GUI::HighlightedStaticText stateText;
    GUI::RectBackplate stateBackplate;
    GUI::StaticText notConnectedText;
    GUI::StaticText notRespondingText;
    GUI::StaticText waitingText;
    GUI::StaticText workingText;

    // Buttons for start/stop device
    GUI::InfoBox activatableBox;
    GUI::ImageButton upButton;
    GUI::ImageButton haltButton;
    GUI::ImageButton downButton;

public:
    DeviceInterface(const Window& window, float X, float Y, float W, float H);
    void reset();

    bool click(const Mouse mouse);
    bool press(SDL_Keycode key);
    void update();
    void blit() const override;
};
