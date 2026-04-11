/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saver.hpp"
#include "../cycles/baseCycle.hpp"

bool Saver::active = false;


Saver::Saver(const Window& _window)
: saveButton(_window, 0.05, 0.05, 0.04, Textures::SaveButton),
notSavedText(_window, 0.08, 0.05, {"Not saved", "Не сохранено"}, Height::Main, WHITE, GUI::Aligment::Left),
savedInfo(_window, 0.5, 0.1, {"Saved", "Сохранено"}),
backplate(_window, 0.5, 0.5, 0.25, 0.22, 10, 2),
menuTitle(_window, 0.5, 0.43, {"Enter file name", "Введите имя файла"}, 1),
fileNameTypeBox(_window, 0.5, 0.5, "Data"),
menuSaveButton(_window, 0.5, 0.58, {"Save", "Сохранить"}),
rewriteOptions(_window, {"Overwrite file?", "Перезаписать файл?"}, {"Yes", "Да"}, {"No", "Нет"}) {}

void Saver::reset() {
    active = false;
}

bool Saver::click(const Mouse _mouse) {
    if (active) {
        // Check, if openned submenu for 
        if (int var = rewriteOptions.click(_mouse)) {
            if (var == 2) {
                // Writing anyway
                BaseCycle::collectedData.saveAnyway(fileNameTypeBox.getString());
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
            if (BaseCycle::collectedData.trySaveNew(fileNameTypeBox.getString())) {
                rewriteOptions.activate();
            } else {
                // Showing, that saved
                savedInfo.reset();
                // Closing this menu
                active = false;
            }
            return true;
        }
        // Check on entering text
        fileNameTypeBox.click(_mouse);
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

void Saver::type(SDL_Keycode _code) {
    if (active) {
        fileNameTypeBox.type(_code);
    }
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
    if (BaseCycle::collectedData.isUpdated()) {
        notSavedText.blit();
    }
    savedInfo.blit();

    if (active) {
        backplate.blit();
        menuTitle.blit();
        fileNameTypeBox.blit();
        menuSaveButton.blit();
        rewriteOptions.blit();
    }
}

