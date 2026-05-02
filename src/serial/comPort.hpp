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
};
