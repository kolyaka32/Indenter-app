/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "comPort.hpp"


// Class for work with serial port
class Serial {
 private:
    // Information for interacting by serial-port
    DCB dcb;
    HANDLE handle = INVALID_HANDLE_VALUE;

 public:
    Serial();
    bool tryConnectTo(const ComPort port);  // Trying connect to specified port, return true if sucsesful
    void reset();
    const void* readData();
    void writeData(const char* data, int length);
};

// Global object for communication throw serial port
extern Serial serial;
