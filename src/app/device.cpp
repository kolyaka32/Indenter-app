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
        // Send to stop
        sendStop();

        // Disconnecting device
        serial.reset();
    }
}

void Device::disconnect() {
    if (state != NotConnected) {
        serial.reset();
    }
    state = NotConnected;
}

bool Device::connectTo(const ComPort _port) {
    if (serial.tryConnectTo(_port)) {
        state = Waiting;
        return false;
    }
    return true;
}

void Device::checkRecieve() {
    if (state != States::NotConnected) {
        // Get new messages
        if (const Uint8* data = (Uint8*)serial.readData()) {
            switch (Get(data[0])) {
            case Get::None:
                // Nothing
                break;

            case Get::Packet:
                collectedData.addFrame(data+1);
                break;

            case Get::ReachPos:
                // !
                break;
                
            case Get::ReachForce:
                // !
                break;

            case Get::Working:
                state = Working;
                break;

            case Get::Waiting:
                state = Waiting;
                break;

            default:
                return;
            }
            // Update timer
            lastRecieve = getTime() + exceedWait;
        } else {
            // Check, if hasn't got packet too long
            if (getTime() > lastRecieve) {
                state = States::NotResponding;
            }
        }        
    }
}

void Device::sendStop() {
    char data = char(Send::Stop);
    serial.writeData(&data, sizeof(data));
}

void Device::sendMoveUp() {
    char data = char(Send::SetWorkUp);
    serial.writeData(&data, sizeof(data));
}

void Device::sendMoveDown() {
    char data = char(Send::SetWorkDown);
    serial.writeData(&data, sizeof(data));
}

void Device::sendIdleUp() {
    char data = char(Send::SetIdleUp);
    serial.writeData(&data, sizeof(data));
}

void Device::sendIdleDown() {
    char data = char(Send::SetIdleDown);
    serial.writeData(&data, sizeof(data));
}

void Device::sendStepUp(int _steps) {
    char data[5];
    data[0] = char(Send::SetStepUp);
    memcpy(data+1, &_steps, sizeof(_steps));
    serial.writeData(data, sizeof(data));
}

void Device::sendStepDown(int _steps) {
    char data[5];
    data[0] = char(Send::SetStepDown);
    memcpy(data+1, &_steps, sizeof(_steps));
    serial.writeData(data, sizeof(data));
}

void Device::sendMoveToPos(int _pos) {
    char data[5];
    data[0] = char(Send::SetMoveTo);
    memcpy(data+1, &_pos, sizeof(_pos));
    serial.writeData(data, sizeof(data));
}

void Device::sendReachForce() {
    char data = char(Send::ReachForce);
    serial.writeData(&data, sizeof(data));
}

void Device::sendLoseForce() {
    char data = char(Send::LostForce);
    serial.writeData(&data, sizeof(data));
}

void Device::sendGetPos() {
    char data = char(Send::GetPos);
    serial.writeData(&data, sizeof(data));
}

bool Device::isConnected() const {
    return state != States::NotConnected;
}
