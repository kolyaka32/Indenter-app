/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "deviceInterface.hpp"
#include "device.hpp"


DeviceInterface::DeviceInterface(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
mainBackplate(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Manual control", "Ручное управление"}, 2, Height::Info),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
portSelectText(_window, _X, _Y-0.35*_H, {"COM-port:", "COM-порт:"}, 2),
serialPort(_window, _X, _Y-0.3*_H, 0.15, 0.04, 2.0),
stateBackplate(_window, _X, _Y-_H*0.1, 0.16, 0.04, 2.0, WHITE),
notConnectedText(_window, _X, _Y-_H*0.1, {"Not connected", "Нет подключения"}, Height::Main, BLACK),
waitingText(_window, _X, _Y-_H*0.1, {"Wait start", "Ожидает начала"}, Height::Main, BLACK),
preWorkingText(_window, _X, _Y-_H*0.1, {"Idle running", "Холостой ход"}, Height::Main, BLACK),
workingText(_window, _X, _Y-_H*0.05, {"Working running", "Рабочий ход"}, Height::Main, BLACK),
startButton(_window, _X, _Y-_H*0.05, {"Start", "Старт"}),
stopButton(_window, _X, _Y-_H*0.05, {"Stop", "Стоп"}) {}

void DeviceInterface::reset() {
    serialPort.reset();
}

bool DeviceInterface::click(const Mouse _mouse) {
    switch (device.state) {
    case Device::Waiting:
        if (startButton.in(_mouse)) {
            device.start();
        }
        break;

    case Device::IdleSpeed:
    case Device::MainSpeed:
        if (startButton.in(_mouse)) {
            device.stop();
        }
        break;
    
    default:
        break;
    }
    return false;
}

void DeviceInterface::update() {
    switch (device.state) {
    case Device::Waiting:
        device.update();
        break;

    case Device::IdleSpeed:
        device.update();
        break;

    case Device::MainSpeed:
        device.update();
        break;
    
    default:
        break;
    }
}

void DeviceInterface::blit() const {
    mainBackplate.blit();

    title.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    portSelectText.blit();
    serialPort.blit();

    // States
    stateBackplate.blit();
    switch (device.state) {
    case Device::NotConnected:
        notConnectedText.blit();
        break;

    case Device::Waiting:
        waitingText.blit();
        startButton.blit();
        break;

    case Device::IdleSpeed:
        preWorkingText.blit();
        stopButton.blit();
        break;

    case Device::MainSpeed:
        workingText.blit();
        stopButton.blit();
        break;
    
    default:
        break;
    }
}
