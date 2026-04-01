/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"

#if (SDL_PLATFORM_WINDOWS)
#include <windows.h>
#endif

// Structure for storing com-ports data and it state
class ComPort {
 private:
   bool avaliable = false;
   char name[6] = "COM0";

 public:
   ComPort(int number);
   bool updateState();  // Update current state of connection and return true, if changed
   bool isAvaliable() const;
   const char* getName() const;
   bool tryOpen();
};



// Class for work with serial port
class Serial {
 private:
    // Flag of current state
    bool avaliable = false;

    // Information for interacting by serial-port
    DCB dcb;
    HANDLE handle = INVALID_HANDLE_VALUE;

 public:
    Serial();
    ~Serial();
    bool tryConnectTo(const ComPort port);  // Trying connect to specified port, return true if sucsesful
    void reset();
    void printState();
    const char* readData();
    void writeData(const char* data, int length);
};

// Global object for communication throw serial port
extern Serial serial;
