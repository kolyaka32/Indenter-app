/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
settings(_window),
serialPort(_window, 0.6, 0.2, 0.12, 0.04) {
    serialPort.reset();
}

bool BaseCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (int var = serialPort.click(mouse)) {
        //
    }
    return false;
}

void BaseCycle::update() {
    settings.update();
    serial.updateConnections();
}

void BaseCycle::inputMouseUp() {
    settings.unClick();
}

void BaseCycle::inputMouseWheel(float _wheelY) {
    settings.scroll(mouse, _wheelY);
}

void BaseCycle::draw() const {
    window.setDrawColor(BLACK);
    window.clear();
    serialPort.blit();
    settings.blit();

    window.render();
}
