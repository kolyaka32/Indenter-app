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
    #if (SDL_PLATFORM_WINDOWS)
    DCB dcb;
    HANDLE handle = INVALID_HANDLE_VALUE;
    #endif
    #if (SDL_PLATFORM_UNIX)
    int fd;  // File descriptor for serial port
    termios portSettings;
    #endif

 public:
    Serial();
    bool tryConnectTo(const ComPort& port);  // Trying connect to specified port, return true if sucsesful
    void reset();
    const void* readData(unsigned* length);
    void writeData(const char* data, int length);
};

// Global object for communication throw serial port
extern Serial serial;
