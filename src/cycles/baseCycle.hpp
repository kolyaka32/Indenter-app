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
#include "../app/programming/programMenu.hpp"


// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 protected:
    SettingsMenu settings;  // Menu for change settings
 
    // Submenu
    GUI::RoundedBackplate mainBackplate;
    GUI::HighlightedStaticText portSelectText;
    CurrentPort serialPort;  // System for selecting port for getting data throw COM-port
    GUI::HighlightedStaticText panelText;
    DeviceInterface deviceInterface;
    Saver saver;

    Chart<Force> forceChart;
    Chart<Temperature> tempertureChart;
    ProgramMenu programMenu;

 protected:
    bool inputMouseDown() override;
    void update() override;
    void inputMouseUp() override;
    bool inputKeys(SDL_Keycode key) override;
    bool inputMouseWheel(float wheelY) override;
    bool inputText(const char* text) override;
    void draw() const override;

 public:
    BaseCycle(Window& _window);
};
