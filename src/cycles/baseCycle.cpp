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
mainBackplate(_window, 0.15, 0.5, 0.28, 0.9, 20.0, 2.0, {140, 140, 140, 255}),
panelText(_window, 0.15, 0.1, {"Control", "Управление"}, 1),
portSelectText(_window, 0.15, 0.15, {"COM-port:", "COM-порт:"}, 1),
serialPort(_window, 0.15, 0.2, 0.12, 0.04),
startButton(_window, 0.15, 0.4, {"Start", "Старт"}),
stopButton(_window, 0.15, 0.4, {"Stop", "Стоп"}),
saver(_window),
forceChart(_window, 0.45, 0.1, 0.4, 0.3, collectedData.getForces(), 0.0, 10.0, {"Force", "Сила"}),
tempertureChart(_window, 0.45, 0.45, 0.4, 0.3, collectedData.getTemperatures(), -40.0, 20.0, {"Temperature", "Температура"}) {
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

void BaseCycle::inputMouseUp() {
    settings.unClick();
    saver.unclick();
}

void BaseCycle::inputKeys(SDL_Keycode _key) {
    if (saver.type(_key)) {
        return;
    }
    if (_key == SDLK_ESCAPE) {
        settings.activate();
    }
}

void BaseCycle::inputMouseWheel(float _wheelY) {
    settings.scroll(mouse, _wheelY);
}

void BaseCycle::inputText(const char* _text) {
    saver.inputText(_text);
}

void BaseCycle::update() {
    settings.update();
    serialPort.update();
    collectedData.update();
    saver.update();
}

void BaseCycle::draw() const {
    // Background
    window.setDrawColor(GREY);
    window.clear();
    
    // Main part
    mainBackplate.blit();
    portSelectText.blit();
    serialPort.blit();
    forceChart.blit();
    tempertureChart.blit();

    // Above menus
    saver.blit();
    
    settings.blit();

    // Render it
    window.render();
}
