/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "device.hpp"
#include "output/collectedData.hpp"
#include "programming/programMenu.hpp"


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
    if (isConnected()) {
        // Apply connection itself
        serial.reset();
        // Stop any executing program
        ProgramMenu::stop();
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
    if (isConnected()) {
        // Get new messages
        if (const Uint8* data = (Uint8*)serial.readData()) {
            switch (Get(data[0])) {
            case Get::None:
                // Nothing
                break;

            case Get::Waiting:
                state = Waiting;
                break;

            case Get::Working:
                state = Working;
                break;

            case Get::Packet:
                collectedData.addFrame(data);
                break;

            case Get::Position:
                ProgramMenu::handlePos(int(*(data+1)));
                break;

            case Get::ReachPos:
                ProgramMenu::handleReachPos();
                break;
                
            case Get::ReachForce:
                ProgramMenu::handleReachForce();
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

void Device::sendWorkUp() {
    char data = char(Send::SetWorkUp);
    serial.writeData(&data, sizeof(data));
}

void Device::sendWorkDown() {
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

void Device::sendStepUp(float _distance) {
    char data[5];
    data[0] = char(Send::SetStepUp);
    memcpy(data+1, &_distance, sizeof(_distance));
    serial.writeData(data, sizeof(data));
}

void Device::sendStepDown(float _distance) {
    char data[5];
    data[0] = char(Send::SetStepDown);
    memcpy(data+1, &_distance, sizeof(_distance));
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
    char data = char(Send::LowerForce);
    serial.writeData(&data, sizeof(data));
}

void Device::sendGetPos() {
    char data = char(Send::GetPos);
    serial.writeData(&data, sizeof(data));
}

bool Device::isConnected() const {
    return state != States::NotConnected;
}
