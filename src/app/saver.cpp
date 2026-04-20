/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saver.hpp"
#include "collectedData.hpp"

bool Saver::active = false;


Saver::Saver(const Window& _window)
: notSavedText(_window, 0.15, 0.85, {"Not saved", "Не сохранено"}, 1),
saveButton(_window, 0.15, 0.9, {"Save", "Сохранить"}),
savedInfo(_window, 0.5, 0.1, {"Saved", "Сохранено"}),
backplate(_window, 0.5, 0.5, 0.25, 0.22, 10, 2),
menuTitle(_window, 0.5, 0.42, {"Enter file name", "Введите имя файла"}, 1),
fileNameTypeBox(_window, 0.5, 0.48, "Data"),
menuSaveButton(_window, 0.5, 0.53, {"Save", "Сохранить"}),
menuCloseButton(_window, 0.5, 0.58, {"Close", "Закрыть"}),
rewriteOptions(_window, {"Overwrite file?", "Перезаписать файл?"}, {"Yes", "Да"}, {"No", "Нет"}) {}

void Saver::reset() {
    active = false;
}

bool Saver::click(const Mouse _mouse) {
    if (active) {
        // Check on entering text
        fileNameTypeBox.click(_mouse);
        // Check, if openned submenu for 
        if (int var = rewriteOptions.click(_mouse)) {
            if (var == 2) {
                // Writing anyway
                collectedData.saveAnyway(fileNameTypeBox.getString());
                // Closing submenu
                rewriteOptions.reset();
                // Showing, that saved
                savedInfo.reset();
                // Closing this menu
                active = false;
            } else if (var == 3) {
                // Closing submenu
                rewriteOptions.reset();
            }
            return true;
        }
        // Check, if trying save
        if (menuSaveButton.in(_mouse)) {
            // Trying save
            if (collectedData.trySaveNew(fileNameTypeBox.getString())) {
                rewriteOptions.activate();
            } else {
                // Showing, that saved
                savedInfo.reset();
                // Closing this menu
                active = false;
            }
            return true;
        }
        // Check on closing
        if (menuCloseButton.in(_mouse)) {
            active = false;
        }
        return false;
    }
    // Check, if activate current menu
    if (saveButton.in(_mouse)) {
        active = true;
        return true;
    }
    return false;
}

void Saver::unclick() {
    fileNameTypeBox.unclick();
}

bool Saver::type(SDL_Keycode _code) {
    if (active) {
        // Check, if close overwrite menu
        if (rewriteOptions.isActive()) {
            if (_code == SDLK_ESCAPE) {
                rewriteOptions.reset();
            }
            return true;
        }
        // Check, if close menu
        if (_code == SDLK_ESCAPE) {
            fileNameTypeBox.unclick();
            active = false;
            return true;
        }
        fileNameTypeBox.type(_code);
        return true;
    }
    return false;
}

void Saver::inputText(const char* _text) {
    fileNameTypeBox.writeString(_text);
}

void Saver::update() {
    savedInfo.update();
    if (active) {
        Mouse mouse;
        mouse.updatePos();
        fileNameTypeBox.update(mouse.getX());
    }
}

void Saver::blit() const {
    saveButton.blit();

    // Showing text, that not saved
    if (collectedData.isUpdated()) {
        notSavedText.blit();
    }
    savedInfo.blit();

    if (active) {
        backplate.blit();
        menuTitle.blit();
        fileNameTypeBox.blit();
        menuSaveButton.blit();
        menuCloseButton.blit();
        rewriteOptions.blit();
    }
}

