/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"

#if (SDL_PLATFORM_WINDOWS)
#include <windows.h>
#endif

// Structure for storing com-ports data
struct ComPort {
   bool avaliable = false;
   char name[6] = "COM0";
   HANDLE handle = INVALID_HANDLE_VALUE;

   ComPort(int number);
   bool tryOpen();
};



// Class for work with serial port
class Serial {
 private:
    // Information for interacting by serial-port
    DCB dcb;

 public:
    Serial();
    ~Serial();
    void printCommState(DCB dcb);
    void updateConnections();
    void tryConnectTo(int port);

    // Array of com-ports
   std::array<ComPort, 4> ports;  // Ports: 3, 4, 5, 6
};

// Global object for communication throw serial port
extern Serial serial;
