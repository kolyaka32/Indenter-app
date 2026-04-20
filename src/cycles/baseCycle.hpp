/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/cycleTemplate.hpp"
#include "../GUI/interface.hpp"
#include "../menu/settingsMenu.hpp"
#include "../app/currentPort.hpp"
#include "../app/collectedData.hpp"
#include "../app/deviceInterface.hpp"
#include "../app/saver.hpp"
#include "../app/chart.cpp"


// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 protected:
    // System for selecting port for getting data throw COM-port
    CurrentPort serialPort;

    // Graphical part
    SettingsMenu settings;  // Menu for change settings

    // Main menu
    GUI::RoundedBackplate mainBackplate;
    GUI::HighlightedStaticText panelText;
    GUI::HighlightedStaticText portSelectText;
    DeviceInterface deviceInterface;
    Saver saver;
    Chart<Force> forceChart;
    Chart<Temperature> tempertureChart;

 protected:
    bool inputMouseDown() override;
    void update() override;
    void inputMouseUp() override;
    void inputKeys(SDL_Keycode key) override;
    void inputMouseWheel(float wheelY) override;
    void inputText(const char* text) override;
    void draw() const override;

 public:
    BaseCycle(Window& _window);
};
