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
        ProgramMenu::program.stop();
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
        unsigned long length = 0;
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
    for (int i=0; i < _length;) {
        switch (Get(*((Type*)_data))) {
        case Get::None:
            // Nothing
            i += sizeof(Type);
            break;

        case Get::Waiting:
            state = Waiting;
            i += sizeof(Type);
            break;

        case Get::Working:
            state = Working;
            i += sizeof(Type);
            break;

        case Get::Packet:
            // One packet of data
            struct DataPacket {
                Type type;
                Padding unused;
                float position;
                float force;
                Uint16 temperature;
            };
            collectedData.addFrame(((DataPacket*)_data)->position, 
                ((DataPacket*)_data)->force, ((DataPacket*)_data)->temperature);
            i += sizeof(DataPacket);
            break;

        case Get::Position:
            struct PosPacket {
                Type type;
                Padding unused;
                int pos;
            };
            ProgramMenu::program.handlePos(((PosPacket*)_data)->pos);
            i += sizeof(PosPacket);
            break;

        case Get::ReachPos:
            ProgramMenu::program.handleReachPos();
            i += sizeof(Type);
            break;

        case Get::ReachForce:
            ProgramMenu::program.handleReachForce();
            i += sizeof(Type);
            break;

        default:
            i += sizeof(Type);
            return;
        }
    }
}

Device::Speed Device::getSendSpeed(unsigned _speed) const {
    switch (_speed) {
    case 1:
        return 1;

    case 2:
        return 4;

    case 3:
        return 10;

    case 4:
        return 25;

    default:
        return 1;
    }
}

void Device::sendStop() {
    struct Packet {
        Type type;
    };
    Packet packet;
    packet.type = Type(Send::SetStop);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendMoveUp(unsigned _speed) {
    struct Packet {
        Type type;
        Speed speed;
    };
    Packet packet;
    packet.type = Type(Send::SetMoveUp);
    packet.speed = getSendSpeed(_speed);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendMoveDown(unsigned _speed) {
    struct Packet {
        Type type;
        Speed speed;
    };
    Packet packet;
    packet.type = Type(Send::SetMoveDown);
    packet.speed = getSendSpeed(_speed);
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendStepUp(unsigned _speed, float _distance) {
    struct Packet {
        Type type;
        Speed speed;
        float distance;
    };
    Packet packet;
    packet.type = Type(Send::SetStepUp);
    packet.speed = getSendSpeed(_speed);
    packet.distance = _distance;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendStepDown(unsigned _speed, float _distance) {
    struct Packet {
        Type type;
        Speed speed;
        float distance;
    };
    Packet packet;
    packet.type = Type(Send::SetStepDown);
    packet.speed = getSendSpeed(_speed);
    packet.distance = _distance;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendMoveToPos(unsigned _speed, int _pos) {
    struct Packet {
        Type type;
        Speed speed;
        int pos;
    };
    Packet packet;
    packet.type = Type(Send::SetMoveTo);
    packet.speed = getSendSpeed(_speed);
    packet.pos = _pos;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendReachForce(float _force) {
    struct Packet {
        Type type;
        Padding unused;
        float force;
    };
    Packet packet;
    packet.type = Type(Send::ReachForce);
    packet.unused = 0;
    packet.force = _force;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendLoseForce(float _force) {
    struct Packet {
        Type type;
        Padding unused;
        float force;
    };
    Packet packet;
    packet.type = Type(Send::LowerForce);
    packet.unused = 0;
    packet.force = _force;
    serial.writeData((char*)&packet, sizeof(packet));
}

void Device::sendGetPos() {
    struct Packet {
        Type type;
    };
    Packet packet;
    packet.type = Type(Send::GetPos);
    serial.writeData((char*)&packet, sizeof(packet));
}

bool Device::isConnected() const {
    return state != States::NotConnected;
}
