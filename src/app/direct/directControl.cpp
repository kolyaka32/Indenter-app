/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "directControl.hpp"
#include "../device.hpp"


DirectControl::DirectControl(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
mainBackplate(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Manual control", "Ручное управление"}, 2, Height::Info),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
portSelectText(_window, _X, _Y-0.35*_H, {"COM-port:", "COM-порт:"}, 2),
serialPort(_window, _X, _Y-0.3*_H, 0.15, 0.04, 2.0),
stateText(_window, _X, _Y-_H*0.14, {"Current state:", "Текущее состояние:"}, 2),
stateBackplate(_window, _X, _Y-_H*0.1, 0.16, 0.04, 2.0, WHITE),
notConnectedText(_window, _X, _Y-_H*0.1, {"Not connected", "Нет подключения"}, Height::Main, BLACK),
notRespondingText(_window, _X, _Y-_H*0.1, {"Not responding", "Нет отвечает"}, Height::Main, BLACK),
waitingText(_window, _X, _Y-_H*0.1, {"Wait", "Ожидает"}, Height::Main, BLACK),
workingText(_window, _X, _Y-_H*0.1, {"Running", "Работает"}, Height::Main, BLACK),
activatableBox(_window, _X, _Y-_H*0.03, {"Not connected", "Не подключён"}, 800),
fastUpButton(_window, _X, _Y+_H*0.05, 0.03, Textures::FastUpButton),
workUpButton(_window, _X, _Y+_H*0.12, 0.03, Textures::UpButton),
haltButton(_window, _X, _Y+_H*0.19, 0.03, Textures::HaltButton),
workDownButton(_window, _X, _Y+_H*0.26, 0.03, Textures::DownButton),
fastDownButton(_window, _X, _Y+_H*0.33, 0.03, Textures::FastDownButton) {}

void DirectControl::reset() {
    serialPort.reset();
}

bool DirectControl::click(const Mouse _mouse) {
    if (serialPort.click(_mouse)) {
        return true;
    }
    if (fastUpButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendIdleUp();
        } else {
            activatableBox.reset();
        }
    }
    if (workUpButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendMoveUp();
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
    if (workDownButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendMoveDown();
        } else {
            activatableBox.reset();
        }
    }
    if (fastDownButton.in(_mouse)) {
        if (device.isConnected()) {
            device.sendIdleDown();
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
    fastUpButton.blit();
    workUpButton.blit();
    haltButton.blit();
    workDownButton.blit();
    fastDownButton.blit();
}
