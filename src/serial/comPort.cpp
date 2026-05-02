/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "comPort.hpp"


ComPort::ComPort(int _number)
: avaliable(false) {
    // Changing number in name to correct
    name[3] = '0' + _number;
}

bool ComPort::updateState() {
    static char lpTargetPath[1000];
    bool previousAvaliable = avaliable;
    avaliable = QueryDosDevice(name, lpTargetPath, 100);

    // Returning true, if changed
    return avaliable != previousAvaliable;
}

bool ComPort::isAvaliable() const {
    return avaliable;
}

const char* ComPort::getName() const {
    return name;
}
