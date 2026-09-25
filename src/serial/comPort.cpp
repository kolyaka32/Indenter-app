/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "comPort.hpp"


#if (SDL_PLATFORM_WINDOWS)
std::array<ComPort, 4> comPorts {{
    {"COM3"},
    {"COM4"},
    {"COM5"},
    {"COM6"}
}};
#endif
#if (SDL_PLATFORM_UNIX)
std::array<ComPort, 1> comPorts {
    {{"/dev/ttyACM0"}}
};
#endif



ComPort::ComPort(const char* _name)
: avaliable(false),
name(_name) {}

bool ComPort::updateState() {
    bool previousAvaliable = avaliable;

    #if (SDL_PLATFORM_WINDOWS)
    static char lpTargetPath[1000];
    avaliable = QueryDosDevice(name, lpTargetPath, 100);
    #endif
    #if (SDL_PLATFORM_UNIX)
    avaliable = (access(name, F_OK) == F_OK);
    #endif

    // Returning true, if changed
    return avaliable != previousAvaliable;
}

bool ComPort::isAvaliable() const {
    return avaliable;
}
