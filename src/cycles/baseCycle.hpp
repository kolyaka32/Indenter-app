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


// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 protected:
    SettingsMenu settings;  // Menu for change settings
    CurrentPort serialPort;
    CollectedData collectedData;

 public:
    bool inputMouseDown() override;
    void update() override;
    void inputMouseUp() override;
    void inputKeys(SDL_Keycode key) override;
    void inputMouseWheel(float _wheelY) override;
    void draw() const override;

 public:
    BaseCycle(Window& _window);
};
