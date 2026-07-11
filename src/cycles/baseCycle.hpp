/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/cycleTemplate.hpp"
#include "../menu/settingsMenu.hpp"
#include "../app/deviceInterface.hpp"
#include "../app/programming/programMenu.hpp"
#include "../app/output/outputMenu.hpp"


// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 protected:
    SettingsMenu settings;

    DeviceInterface deviceInterface;
    ProgramMenu programMenu;
    OutputMenu outputMenu;

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
