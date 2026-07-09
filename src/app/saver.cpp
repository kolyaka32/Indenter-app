/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saver.hpp"
#include "collectedData.hpp"


Saver::Saver(const Window& _window, float _X, float _Y)
: SubWindow(_window, 0.5, 0.5, 0.25, 0.22),
notSavedText(_window, _X, _Y-0.05, {"Not saved", "Не сохранено"}, 1),
saveButton(_window, _X, _Y, {"Save", "Сохранить"}),
savedInfo(_window, 0.5, 0.1, {"Saved", "Сохранено"}),
menuTitle(_window, 0.5, 0.42, {"Enter file name", "Введите имя файла"}, 1),
fileNameTypeBox(_window, 0.5, 0.48, "Data"),
menuSaveButton(_window, 0.5, 0.53, {"Save", "Сохранить"}),
menuCloseButton(_window, 0.5, 0.58, {"Close", "Закрыть"}),
rewriteOptions(_window, 0.5, 0.5, 0.6, 0.4,
    {"Overwrite file?", "Перезаписать файл?"}, {"Yes", "Да"}, {"No", "Нет"}) {}

bool Saver::click(const Mouse _mouse) {
    if (active) {
        // Check, if openned submenu for 
        if (GUI::Code code = rewriteOptions.click(_mouse)) {
            if (code == GUI::Button1) {
                // Writing anyway
                collectedData.saveAnyway(fileNameTypeBox.getString());
                // Closing submenu
                rewriteOptions.reset();
                // Showing, that saved
                savedInfo.reset();
                // Closing this menu
                active = false;
            } else if (code == GUI::Button2) {
                // Closing submenu
                rewriteOptions.reset();
            }
            return true;
        }
        // Check, if entering text
        fileNameTypeBox.checkOff(_mouse);
        if (fileNameTypeBox.click(_mouse)) {
            return true;
        }
        // Check, if trying save
        if (menuSaveButton.in(_mouse)) {
            trySave();
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
        // Check typing
        if (GUI::Code code = fileNameTypeBox.type(_code)) {
            if (code == GUI::Activate) {
                trySave();
            }
            return true;
        }
        // Check, if close overwrite menu
        if (rewriteOptions.isOpen()) {
            if (_code == SDLK_ESCAPE) {
                rewriteOptions.reset();
            }
            return true;
        }
        // Check, if close menu
        if (_code == SDLK_ESCAPE) {
            fileNameTypeBox.unclick();
            close();
            return true;
        }
        return true;
    }
    return false;
}

bool Saver::inputText(const char* _text) {
    fileNameTypeBox.writeString(_text);
    return true;
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
        background.blit();
        menuTitle.blit();
        fileNameTypeBox.blit();
        menuSaveButton.blit();
        menuCloseButton.blit();
        rewriteOptions.blit();
    }
}

void Saver::trySave() {
    if (collectedData.trySaveNew(fileNameTypeBox.getString())) {
        rewriteOptions.open();
    } else {
        // Showing, that saved
        savedInfo.reset();
        // Closing this menu
        active = false;
    }
}
