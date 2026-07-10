/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "texturesNames.hpp"

#if (PRELOAD_TEXTURES)


// File names of the corresponding textures
const char* texturesFilesNames[unsigned(Textures::Count)] = {
    // Graphic interface sprites
    "img/GUI/slider_button.png",
    "img/GUI/slider_line.png",

    "img/GUI/quit_button.png",
    "img/GUI/menu_button.png",
    "img/GUI/settings_button.png",
    "img/GUI/save_button.png",
    "img/GUI/restart_button.png",
    "img/GUI/resume_pause_button.png",
    "img/GUI/halt_button.png",

    // Flags
    "img/GUI/Flag_USA.png",
    "img/GUI/Flag_RUS.png",

    "img/program/Start.png",
    "img/program/LoopStart.png",
    "img/program/LoopMiddle.png",
    "img/program/LoopEnd.png",
    "img/program/WhileEnd.png",
    "img/program/Action.png",
    "img/program/Wait.png",
};

Textures operator+(const Textures _color, int _offset) {
    return Textures(unsigned(_color) + _offset);
}

Textures operator-(const Textures _color, int _offset) {
    return Textures(unsigned(_color) - _offset);
}

#endif  // (PRELOAD_TEXTURES)
