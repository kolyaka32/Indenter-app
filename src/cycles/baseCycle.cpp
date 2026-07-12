/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
settings(_window),
deviceInterface(_window, 0.12, 0.55, 0.24, 0.9),
programMenu(_window, 0.46, 0.55, 0.44, 0.9),
outputMenu(_window, 0.84, 0.55, 0.32, 0.9) {
    if (!isRestarted()) {
        deviceInterface.reset();
        programMenu.reset();
        outputMenu.reset();
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
    if (outputMenu.click(mouse)) {
        return true;
    }
    return false;
}

void BaseCycle::inputMouseUp() {
    settings.unClick();
}

bool BaseCycle::inputKeys(SDL_Keycode _key) {
    if (deviceInterface.press(_key)) {
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
    return false;
}

void BaseCycle::update() {
    settings.update();
    deviceInterface.update();
    programMenu.update();
    outputMenu.update();
}

void BaseCycle::draw() const {
    // Background
    window.setDrawColor(GREY);
    window.clear();

    deviceInterface.blit();
    programMenu.blit();
    outputMenu.blit();
    settings.blit();

    // Render it
    window.render();
}
