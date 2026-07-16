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

void Device::connectTo(const ComPort _port) {
    if (serial.tryConnectTo(_port)) {
        state = Waiting;
    }
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
    state = States::Working;
}

void Device::sendMoveUp() {
    char data = char(Send::SetMoveUp);
    serial.writeData(&data, sizeof(data));
    state = States::Working;
}

void Device::sendMoveDown() {
    char data = char(Send::SetMoveDown);
    serial.writeData(&data, sizeof(data));
    state = States::Working;
}

void Device::sendRunUp() {
    char data = char(Send::SetRunUp);
    serial.writeData(&data, sizeof(data));
    state = States::Working;
}

void Device::sendRunDown() {
    char data = char(Send::SetRunDown);
    serial.writeData(&data, sizeof(data));
    state = States::Working;
}

void Device::sendReachPos(int _pos) {
    char data[5];
    data[0] = char(Send::ReachPos);
    memcpy(data+1, &_pos, sizeof(_pos));
    serial.writeData(data, sizeof(data));
}

void Device::sendReachForce() {
    char data[1];
    data[0] = char(Send::ReachForce);
    serial.writeData(data, sizeof(data));
}

bool Device::isConnected() const {
    return state != States::NotConnected;
}
