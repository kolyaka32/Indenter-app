/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "currentPort.hpp"


bool CurrentPort::openned = false;
int CurrentPort::selected = 0;

CurrentPort::CurrentPort(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
texts {
    {_window, _X+arrow, _Y+_H*0, {"Not selected", "Не выбран"}, Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y+_H*1, {serial.ports[0].name},        Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y+_H*2, {serial.ports[1].name},        Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y+_H*3, {serial.ports[2].name},        Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y+_H*4, {serial.ports[3].name},        Height::Main, BLACK, GUI::Aligment::Left},
} {
    background = {_window.getWidth()*_X, _window.getHeight()*(_Y-_H/2),
        _window.getWidth()*_W, _window.getHeight()*_H};
}

CurrentPort::~CurrentPort() {}

void CurrentPort::reset() {
    // Checking, if any ports avaliable
    selected = 0;
    serial.updateConnections();

    for (int i=0; i < serial.ports.size(); ++i) {
        if (serial.ports[i].avaliable) {
            selected = i + 1;
            return;
        }
    }
}

int CurrentPort::click(const Mouse _mouse) {
    if (_mouse.in(background)) {
        if (openned) {
            // In openned menu - selecting variant
            // Selecting object
            openned = false;
            background.h /= 5;
            // Return selected variant
            return (_mouse.getY() - background.y) / background.h + 1;
        } else {
            // Openning menu
            openned = true;
            background.h *= 5;
            return 0;
        }
    } else {
        if (openned) {
            background.h /= 5;
            openned = false;
        }
    }
    return false;
}

void CurrentPort::blit() const {
    window.setDrawColor(WHITE);
    window.drawRect(background);

    // Check, if openned
    if (openned) {
        // Draw empty variant
        texts[0].blit();
        // Draw com variants
        for (int i=0; i < 4; ++i) {
            if (serial.ports[i].avaliable) {
                texts[i+1].blit();
            }
        }
    } else {
        //
        texts[0].blit();
    }
}

