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
    GUI::HighlightedStaticText portSelectText;
    CurrentPort serialPort;

    // Texts, showing current state
    GUI::RectBackplate stateBackplate;
    GUI::StaticText notConnectedText;
    GUI::StaticText waitingText;
    GUI::StaticText preWorkingText;
    GUI::StaticText workingText;

    // Buttons for start/stop device
    GUI::TextButton startButton;
    GUI::TextButton stopButton;

public:
    DeviceInterface(const Window& window, float X, float Y, float W, float H);
    void reset();

    bool click(const Mouse mouse);
    void update();
    void blit() const override;
};
