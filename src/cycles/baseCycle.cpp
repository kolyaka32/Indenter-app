/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
settings(_window),
deviceInterface(_window, 0.125, 0.55, 0.25, 0.9),
programMenu(_window, 0.5, 0.55, 0.5, 0.9),
forceChart(_window, 0.4, 0.1, 0.55, 0.35, collectedData.getForces(), 0.0, 10.0, {"Force", "Сила"}),
tempertureChart(_window, 0.4, 0.6, 0.55, 0.35, collectedData.getTemperatures(), -40.0, 20.0, {"Temperature", "Температура"}),
saver(_window, 0.13, 0.9) {
    if (!isRestarted()) {
        deviceInterface.reset();
        saver.reset();
    }
}

bool BaseCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (deviceInterface.click(mouse)) {
        return true;
    }
    if (programMenu.click(mouse)) {
        return true;
    }
    if (saver.click(mouse)) {
        return true;
    }
    return false;
}

void BaseCycle::inputMouseUp() {
    settings.unClick();
    saver.unclick();
}

bool BaseCycle::inputKeys(SDL_Keycode _key) {
    if (saver.type(_key)) {
        return true;
    }
    if (_key == SDLK_ESCAPE) {
        settings.toggle();
        return true;
    }
    return false;
}

bool BaseCycle::inputMouseWheel(float _wheelY) {
    return settings.scroll(mouse, _wheelY);
}

bool BaseCycle::inputText(const char* _text) {
    return saver.inputText(_text);
}

void BaseCycle::update() {
    settings.update();
    deviceInterface.update();
    programMenu.update();
    saver.update();
}

void BaseCycle::draw() const {
    // Background
    window.setDrawColor(GREY);
    window.clear();

    deviceInterface.blit();

    forceChart.blit();
    tempertureChart.blit();
    programMenu.blit();

    // Above menus
    saver.blit();

    settings.blit();

    // Render it
    window.render();
}
