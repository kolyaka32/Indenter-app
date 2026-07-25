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
    struct Packet {
        Uint16 type;
        Uint16 speed;
    };
    Packet packet;
    packet.type = Uint16(Send::Stop);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendMoveUp(Uint16 _speed) {
    struct Packet {
        Uint16 type;
        Uint16 speed;
    };
    Packet packet;
    packet.type = Uint16(Send::SetMoveUp);
    packet.speed = _speed;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendMoveDown(Uint16 _speed) {
    struct Packet {
        Uint16 type;
        Uint16 speed;
    };
    Packet packet;
    packet.type = Uint16(Send::SetMoveDown);
    packet.speed = _speed;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendStepUp(Uint16 _speed, float _distance) {
    struct Packet {
        Uint16 type;
        Uint16 speed;
        float distance;
    };
    Packet packet;
    packet.type = Uint16(Send::SetStepUp);
    packet.speed = _speed;
    packet.distance = _distance;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendStepDown(Uint16 _speed, float _distance) {
    struct Packet {
        Uint16 type;
        Uint16 speed;
        float distance;
    };
    Packet packet;
    packet.type = Uint16(Send::SetStepDown);
    packet.speed = _speed;
    packet.distance = _distance;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendMoveToPos(Uint16 _speed, int _pos) {
    struct Packet {
        Uint16 type;
        Uint16 speed;
        int pos;
    };
    Packet packet;
    packet.type = Uint16(Send::SetMoveTo);
    packet.speed = _speed;
    packet.pos = _pos;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendReachForce(float _force) {
    struct Packet {
        Uint16 type;
        float force;
    };
    Packet packet;
    packet.type = Uint16(Send::ReachForce);
    packet.force = _force;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendLoseForce(float _force) {
    struct Packet {
        Uint16 type;
        float force;
    };
    Packet packet;
    packet.type = Uint16(Send::LowerForce);
    packet.force = _force;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendGetPos() {
    struct Packet {
        Uint16 type;
    };
    Packet packet;
    packet.type = Uint16(Send::GetPos);
    serial.writeData((char*)&packet, sizeof(packet));
}

bool Device::isConnected() const {
    return state != States::NotConnected;
}
