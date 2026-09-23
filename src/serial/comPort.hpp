/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "../data/app.hpp"

#if (SDL_PLATFORM_WINDOWS)
#include <windows.h>
#elif (SDL_PLATFORM_UNIX)
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#else
#error "Can't find avaliable COM port library"
#endif


// Structure for storing com-ports data and it state
class ComPort {
 private:
    bool avaliable = false;
    #if (SDL_PLATFORM_WINDOWS)
    char name[6] = "COM0";
    #endif
    #if (SDL_PLATFORM_UNIX)
    char name[15] = "/dev/ttyACM0";
    #endif

 public:
    ComPort(int number);
    bool updateState();  // Update current state of connection and return true, if changed
    bool isAvaliable() const;
    const char* getName() const;
};

// Array of avaliable com-ports
#if (SDL_PLATFORM_WINDOWS)
// COM ports: 3, 4, 5, 6
extern std::array<ComPort, 4> comPorts;
#endif
#if (SDL_PLATFORM_UNIX)
// TTY port
extern std::array<ComPort, 1> comPorts;
#endif
