/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"

#if (PRELOAD_FONTS)


// Names of fonts
enum class Fonts {
    Main,  // Main using font (now only one)

    // Global counter of all loaded fonts
    Count,
};

// File names of the corresponding fonts
extern const char* fontsFilesNames[unsigned(Fonts::Count)];

#endif  // (PRELOAD_FONTS)
