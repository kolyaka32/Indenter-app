/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "device.hpp"
#include "collectedData.hpp"


Device device;


Device::Device() {}

Device::~Device() {
    if (state) {
        // Disconnecting device
        serial.reset();
    }
}

void Device::disconnect() {
    state = NotConnected;
    if (state != NotConnected) {
        serial.reset();
    }
}

void Device::connectTo(const ComPort _port) {
    if (serial.tryConnectTo(_port)) {
        state = Waiting;
    }
}

void Device::start() {
    if (state) {
        state = IdleSpeed;
    }
}

void Device::stop() {
    if (state) {
        state = Waiting;
    }
}

void Device::update() {
    // Check, if changed state
    // Get new messages
    // !
    if (const void* data = serial.readData()) {
        collectedData.addFrame((char*)data);
    }
}
