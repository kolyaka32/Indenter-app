/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
settings(window) {}

bool BaseCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    return false;
}

void BaseCycle::update() {
    settings.update();
    serial.printStatus();
}

void BaseCycle::inputMouseUp() {
    settings.unClick();
}

void BaseCycle::inputMouseWheel(float _wheelY) {
    settings.scroll(mouse, _wheelY);
}
