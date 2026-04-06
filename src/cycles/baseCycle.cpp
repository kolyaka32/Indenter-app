/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
settings(_window),
serialPort(_window, 0.6, 0.2, 0.12, 0.04),
collectedData(_window) {
    serialPort.reset();
}

bool BaseCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (serialPort.click(mouse)) {
        return true;
    }
    return false;
}

void BaseCycle::update() {
    settings.update();
    serialPort.update();
    collectedData.update();
}

void BaseCycle::inputMouseUp() {
    settings.unClick();
}

void BaseCycle::inputKeys(SDL_Keycode _key) {
    
}

void BaseCycle::inputMouseWheel(float _wheelY) {
    settings.scroll(mouse, _wheelY);
}

void BaseCycle::draw() const {
    window.setDrawColor(GREY);
    window.clear();
    serialPort.blit();
    settings.blit();
    collectedData.blit();

    window.render();
}
