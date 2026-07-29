/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "directControl.hpp"
#include "../device.hpp"


DirectControl::DirectControl(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
mainBackplate(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Manual control", "Ручное управление"},
    2, GUI::Aligment::Midle, Height::Info),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
portSelectText(_window, _X, _Y-0.35*_H, {"COM-port:", "COM-порт:"}, 2),
serialPort(_window, _X, _Y-0.3*_H, 0.15, 0.04, 2.0),
stateText(_window, _X, _Y-_H*0.14, {"Current state:", "Текущее состояние:"}, 2),
stateBackplate(_window, _X, _Y-_H*0.1, 0.16, 0.04, 2.0, WHITE),
notConnectedText(_window, _X, _Y-_H*0.1, {"Not connected", "Нет подключения"},
    GUI::Aligment::Midle, Height::Main, BLACK),
notRespondingText(_window, _X, _Y-_H*0.1, {"Not responding", "Не отвечает"},
    GUI::Aligment::Midle, Height::Main, BLACK),
waitingText(_window, _X, _Y-_H*0.1, {"Wait", "Ожидает"},
    GUI::Aligment::Midle, Height::Main, BLACK),
workingText(_window, _X, _Y-_H*0.1, {"Running", "Работает"},
    GUI::Aligment::Midle, Height::Main, BLACK),
activatableBox(_window, _X, _Y-_H*0.05, {"Not connected", "Не подключён"}, 800),
slowUpButton(_window,   _X-0.035, _Y+_H*0.08, 0.03, Textures::SlowUpButton),
normalUpButton(_window, _X,       _Y+_H*0.08, 0.03, Textures::NormalUpButton),
fastUpButton(_window,   _X+0.035, _Y+_H*0.08, 0.03, Textures::FastUpButton),
haltButton(_window,     _X,       _Y+_H*0.16, 0.03, Textures::HaltButton),
slowDownButton(_window, _X-0.035, _Y+_H*0.24, 0.03, Textures::SlowDownButton),
normalDownButton(_window, _X,     _Y+_H*0.24, 0.03, Textures::NormalDownButton),
fastDownButton(_window, _X+0.035, _Y+_H*0.24, 0.03, Textures::FastDownButton) {}

void DirectControl::reset() {
    serialPort.reset();
}

bool DirectControl::click(const Mouse _mouse) {
    if (serialPort.click(_mouse)) {
        return true;
    }
    if (slowUpButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendMoveDown(1);
        } else {
            activatableBox.reset();
        }
    }
    if (normalUpButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendMoveDown(2);
        } else {
            activatableBox.reset();
        }
    }
    if (fastUpButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendMoveDown(3);
        } else {
            activatableBox.reset();
        }
    }
    if (haltButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendStop();
        } else {
            activatableBox.reset();
        }
    }
    if (slowDownButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendMoveUp(1);
        } else {
            activatableBox.reset();
        }
    }
    if (normalDownButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendMoveUp(2);
        } else {
            activatableBox.reset();
        }
    }
    if (fastDownButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendMoveUp(3);
        } else {
            activatableBox.reset();
        }
    }
    return false;
}

bool DirectControl::press(SDL_Keycode _key) {
    if (serialPort.press(_key)) {
        return true;
    }
    return false;
}

void DirectControl::update() {
    device.checkRecieve();
    serialPort.update();
    activatableBox.update();
}

void DirectControl::blit() const {
    mainBackplate.blit();

    title.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    portSelectText.blit();
    serialPort.blit();

    // States
    stateText.blit();
    stateBackplate.blit();
    switch (device.state) {
    case Device::NotConnected:
        notConnectedText.blit();
        break;

    case Device::NotResponding:
        notRespondingText.blit();
        break;

    case Device::Waiting:
        waitingText.blit();
        break;

    case Device::Working:
        workingText.blit();
        break;
    
    default:
        break;
    }
    activatableBox.blit();
    slowUpButton.blit();
    normalUpButton.blit();
    fastUpButton.blit();
    haltButton.blit();
    slowDownButton.blit();
    normalDownButton.blit();
    fastDownButton.blit();
}
