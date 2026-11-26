/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "fileDialog.hpp"


FileDialog::FileDialog(const Window& _window, const char* _folder, const LanguagedText&& _filter, const char* _pattern,
    const char* _baseName)
: window(_window),
filter{nullptr, _pattern} {
    SDL_CreateDirectory(_folder);
    SDL_snprintf(filterText, sizeof(filterText), "%s", _filter.getString().c_str());
    filter.name = filterText;
    char* directory = SDL_GetCurrentDirectory();
    SDL_snprintf(saveLocation, sizeof(saveLocation), "%s%s\\%s.%s", directory, _folder, _baseName, _pattern);
    SDL_free(directory);
}

void FileDialog::showSave(SDL_DialogFileCallback _callback, void* _argument) const {
    window.showSaveFileDialog(_callback, &filter, 1, saveLocation, _argument);
}

void FileDialog::showOpen(SDL_DialogFileCallback _callback, void* _argument) const {
    window.showOpenFileDialog(_callback, &filter, 1, saveLocation, false, _argument);
}
