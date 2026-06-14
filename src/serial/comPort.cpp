/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "comPort.hpp"


std::array<ComPort, 4> comPorts {
    {{3}, {4}, {5}, {6}}
};

ComPort::ComPort(int _number)
: avaliable(false) {
    // Changing number in name to correct
    name[3] = '0' + _number;
}

bool ComPort::updateState() {
    bool previousAvaliable = avaliable;

    #if (!CHECK_CORRECTION)
    static char lpTargetPath[1000];
    avaliable = QueryDosDevice(name, lpTargetPath, 100);
    #endif

    // Returning true, if changed
    return avaliable != previousAvaliable;
}

bool ComPort::isAvaliable() const {
    return avaliable;
}

const char* ComPort::getName() const {
    return name;
}
