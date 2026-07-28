/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <mutex>
#include "outputMenu.hpp"


OutputMenu::OutputMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
mainBackplate(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Getted data", "Полученные данные"}, 2, Height::Info),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
forceChart(_window, _X+0.015, _Y-0.2*_H, _W*0.85, _H*0.25,
    collectedData.getPositions(), collectedData.getForces(), {"Force", "Сила"}, RED),
tempertureChart(_window, _X+0.015, _Y+0.1*_H, _W*0.85, _H*0.25,
    collectedData.getPositions(), collectedData.getTemperatures(), {"Temperature", "Температура"}, BLUE),
forceText(_window, _X-0.08, _Y+_H*0.25, {"Last force: %.1f", "Последние усилие: %.1f"}, Height::Main, WHITE, GUI::Aligment::Left),
tempText(_window, _X-0.08, _Y+_H*0.30, {"Last temperature: %.1f", "Последняя температура: %.1f"}, Height::Main, WHITE, GUI::Aligment::Left),
counterText(_window, _X, _Y+_H*0.35, {"Packets getted: %d", "Пакетов получено: %d"}),
notSavedText(_window, _X, _Y+_H*0.4, {"Not saved", "Не сохранено"}, 1),
saveButton(_window, _X, _Y+_H*0.45, {"Save", "Сохранить"}),
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
    return false;
}

void OutputMenu::update() {
    counterText.setValues(collectedData.getLineCount());
    forceChart.update();
    tempertureChart.update();
    forceText.setValues(collectedData.getLastForce());
    tempText.setValues(collectedData.getLastTemp());
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
}

void OutputMenu::save(void* _userdata, const char* const* _filelist, int _filter) {
    // Check, if all avaliable
    if (_filelist == nullptr || _filter < 0) {
        return;
    }
    // Getting file
    SDL_IOStream* fout = SDL_IOFromFile(*_filelist, "w");
    if (fout == nullptr) {
        return;
    }
    // Locking, while saving
    static std::mutex saveMutex;
    saveMutex.lock();

    // Writing data itself
    collectedData.save(fout);

    saveMutex.unlock();
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", *_filelist);
}
