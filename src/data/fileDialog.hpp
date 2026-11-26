/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include <SDL3/SDL_dialog.h>
#include "window.hpp"


// System for work with file dialogs (save/load files)
class FileDialog {
private:
    const Window& window;
    SDL_DialogFileFilter filter;  // Filter for selection data file
    char filterText[100];
    char saveLocation[100];  // Location with directory for save/load

public:
    FileDialog(const Window& window, const char* folder, const LanguagedText&& filter, const char* pattern,
        const char* baseName);

    void showSave(SDL_DialogFileCallback callback, void* argument = nullptr) const;
    void showOpen(SDL_DialogFileCallback callback, void* argument = nullptr) const;
};
