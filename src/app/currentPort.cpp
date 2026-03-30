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
    {_window, _X+_W*0, _Y, {"Not selected", "Не выбран"}},
    {_window, _X+_W*1, _Y, {serial.ports[0].name}},
    {_window, _X+_W*2, _Y, {serial.ports[1].name}},
    {_window, _X+_W*3, _Y, {serial.ports[2].name}},
    {_window, _X+_W*4, _Y, {serial.ports[3].name}},
} {
    background = {_window.getWidth()*_X, _window.getHeight()*_Y,
        _window.getWidth()*_W, _window.getHeight()*_H};
}

CurrentPort::~CurrentPort() {

}

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
            background.h /= serial.portCount;
            // Return selected variant
            return (_mouse.getY() - background.y) / background.h + 1;
        } else {
            // Openning menu
            openned = true;
            background.h *= serial.portCount;
            return 0;
        }
    }
    return false;
}

void CurrentPort::blit() const {

}

