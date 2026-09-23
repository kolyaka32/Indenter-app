/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "comPort.hpp"


#if (SDL_PLATFORM_WINDOWS)
std::array<ComPort, 4> comPorts {
    {{3}, {4}, {5}, {6}}
};
#endif
#if (SDL_PLATFORM_UNIX)
std::array<ComPort, 1> comPorts {
    {{0}}
};
#endif



ComPort::ComPort(int _number)
: avaliable(false) {
    #if (SDL_PLATFORM_WINDOWS)
    // Changing number in name to correct
    name[3] = '0' + _number;
    #endif
}

bool ComPort::updateState() {
    bool previousAvaliable = avaliable;

    #if (SDL_PLATFORM_WINDOWS)
    static char lpTargetPath[1000];
    avaliable = QueryDosDevice(name, lpTargetPath, 100);
    #endif
    #if (SDL_PLATFORM_UNIX)
    // ! For test
    avaliable = true;
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
