/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


// Static objects
CollectedData BaseCycle::collectedData{};

BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
settings(_window),
portSelectText(_window, 0.09, 0.15, {"COM-port:", "COM-порт:"}, 1),
serialPort(_window, 0.03, 0.2, 0.12, 0.04),
saver(_window) {
    if (!isRestarted()) {
        serialPort.reset();
        saver.reset();
    }
}

bool BaseCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (saver.click(mouse)) {
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
    saver.update();
}

void BaseCycle::inputMouseUp() {
    settings.unClick();
    saver.unclick();
}

void BaseCycle::inputKeys(SDL_Keycode _key) {
    saver.type(_key);
}

void BaseCycle::inputMouseWheel(float _wheelY) {
    settings.scroll(mouse, _wheelY);
}

void BaseCycle::draw() const {
    // Background
    window.setDrawColor(GREY);
    window.clear();
    
    // Main part
    portSelectText.blit();
    serialPort.blit();
    collectedData.blit(window);

    // Above menus
    saver.blit();
    
    settings.blit();

    // Render it
    window.render();
}
