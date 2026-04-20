/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "deviceInterface.hpp"
#include "device.hpp"


DeviceInterface::DeviceInterface(const Window& _window, float _X, float _Y)
: Template(_window),
stateBackplate(_window, _X, _Y, 0.2, 0.04, 2.0),
notConnectedText(_window, _X, _Y, {"Not connected", "Нет подключения"}, Height::Main, BLACK),
waitingText(_window, _X, _Y, {"Not connected", "Нет подключения"}, Height::Main, BLACK),
preWorkingText(_window, _X, _Y, {"Not connected", "Нет подключения"}, Height::Main, BLACK),
workingText(_window, _X, _Y+0.05, {"Not connected", "Нет подключения"}, Height::Main, BLACK),
startButton(_window, _X, _Y+0.05, {"Start", "Старт"}),
stopButton(_window, _X, _Y+0.05, {"Stop", "Стоп"}) {}

void DeviceInterface::click(const Mouse _mouse) {
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
}

void DeviceInterface::blit() const {
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
