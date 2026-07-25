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
        DWORD length = 0;
        const void* data = serial.readData(&length);

        if (data) {
            // Update timer
            lastRecieve = getTime() + exceedWait;
            parseMessage((char*)data, length);
        } else {
            // Check, if hasn't got packet too long
            if (getTime() > lastRecieve) {
                state = States::NotResponding;
            }
        }        
    }
}

void Device::parseMessage(const char* _data, unsigned _length) {
    for (int i=0; i < _length; i += 4) {
        switch (Get(_data[i])) {
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
            // One packet of data
            struct DataPacket {
                // Values
                int type;
                float position;
                float force;
                Uint16 temperature;
            };
            collectedData.addFrame(((DataPacket*)_data)->position, 
                ((DataPacket*)_data)->force, ((DataPacket*)_data)->temperature/10.0);
            i += sizeof(DataPacket) - 4;
            break;

        case Get::Position:
            struct PosPacket {
                int type;
                int pos;
            };
            ProgramMenu::handlePos(((PosPacket*)_data)->pos);
            i += sizeof(PosPacket) - 4;
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
    }
}

void Device::sendStop() {
    int packet = int(Send::Stop);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendWorkUp() {
    int packet = int(Send::SetWorkUp);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendWorkDown() {
    int packet = int(Send::SetWorkDown);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendIdleUp() {
    int packet = int(Send::SetIdleUp);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendIdleDown() {
    int packet = int(Send::SetIdleDown);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendStepUp(float _distance) {
    struct Packet {
        int type;
        float distance;
    };
    Packet packet;
    packet.type = int(Send::SetStepUp);
    packet.distance = _distance;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendStepDown(float _distance) {
    struct Packet {
        int type;
        float distance;
    };
    Packet packet;
    packet.type = int(Send::SetStepDown);
    packet.distance = _distance;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendMoveToPos(int _pos) {
    struct Packet {
        int type;
        int pos;
    };
    Packet packet;
    packet.type = int(Send::SetMoveTo);
    packet.pos = _pos;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendReachForce() {
    char data = char(Send::ReachForce);
    serial.writeData((char*)&data, sizeof(data));
}

void Device::sendLoseForce() {
    char data = char(Send::LowerForce);
    serial.writeData((char*)&data, sizeof(data));
}

void Device::sendGetPos() {
    char data = char(Send::GetPos);
    serial.writeData((char*)&data, sizeof(data));
}

bool Device::isConnected() const {
    return state != States::NotConnected;
}
