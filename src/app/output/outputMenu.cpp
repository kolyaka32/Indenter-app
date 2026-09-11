/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "outputMenu.hpp"


char* OutputMenu::saveName = nullptr;

OutputMenu::OutputMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
mainBackplate(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, {"Getted data", "Полученные данные"}, {_X, _Y-_H*0.45f, .frame=2, .height=GUI::Info, .horAli=GUI::Midle}),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
forceChart(_window, _X+0.015, _Y-0.22*_H, _W*0.85, _H*0.25,
    collectedData.getPositions(), collectedData.getForces(), {"Force", "Сила"}, RED),
tempertureChart(_window, _X+0.015, _Y+0.1*_H, _W*0.85, _H*0.25,
    collectedData.getPositions(), collectedData.getTemperatures(), {"Temperature", "Температура"}, BLUE),
forceText(_window, {"Last force: %.1f", "Последние усилие: %.1f"},
    {_X-(LanguagedText::getLanguage()==Language::Russian ? 0.055f : 0.035f), _Y+_H*0.29f, .frame=1, .horAli=GUI::Left}),
tempText(_window, {"Last temperature: %.1f", "Последняя температура: %.1f"},
    {_X-(LanguagedText::getLanguage()==Language::Russian ? 0.075f : 0.06f), _Y+_H*0.33f, .frame=1, .horAli=GUI::Left}),
counterText(_window, {"Packets getted: %d", "Пакетов получено: %d"}, {_X, _Y+_H*0.37f, .frame=1}),
notSavedText(_window, {"Not saved", "Не сохранено"}, {_X, _Y+_H*0.41f, .frame=1}),
saveButton(_window, {"Save", "Сохранить"}, {_X-_W*0.15f, _Y+_H*0.45f, .frame=1}),
folderButton(window, {"Open folder", "Открыть папку"}, {_X+_W*0.15f, _Y+_H*0.45f, .frame=1}),
filterText{"Table", "Таблица"},
filter{filterText.getString().c_str(), "csv"} {
    // Getting location
    char* directory = SDL_GetCurrentDirectory();
    SDL_CreateDirectory("records");
    snprintf(saveLocation, sizeof(saveLocation), "%srecords\\data.csv", directory);
    SDL_free(directory);

    reset();
}

void OutputMenu::reset() {
    counterText.setValues(0);
}

bool OutputMenu::click(const Mouse _mouse) {
    if (saveButton.in(_mouse)) {
        window.showSaveFileDialog(save, &filter, 1, saveLocation);
        return true;
    }
    if (folderButton.in(_mouse)) {
        char buffer[100];
        char* directory = SDL_GetCurrentDirectory();
        SDL_snprintf(buffer, sizeof(buffer), "file:///%srecords/", directory);
        SDL_free(directory);
        SDL_OpenURL(buffer);
        return true;
    }
    return false;
}

void OutputMenu::update() {
    counterText.setValues(collectedData.getLineCount());
    forceChart.update();
    tempertureChart.update();
    forceText.setValues(collectedData.getLastForce());
    tempText.setValues(collectedData.getLastTemp());
    // Check on saving
    if (saveName) {
        // Writing data itself
        collectedData.save(saveName);
        SDL_free(saveName);
        saveName = nullptr;
    }
}

void OutputMenu::blit() const {
    mainBackplate.blit();
    title.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    forceChart.blit();
    tempertureChart.blit();
    forceText.blit();
    tempText.blit();

    counterText.blit();
    if (collectedData.isUpdated()) {
        notSavedText.blit();
    }
    saveButton.blit();
    folderButton.blit();
}

void OutputMenu::save(void* _userdata, const char* const* _filelist, int _filter) {
    // Check, if all avaliable
    if (_filelist == nullptr || _filter < 0) {
        return;
    }
    SDL_asprintf(&saveName, "%s", *_filelist);
}
