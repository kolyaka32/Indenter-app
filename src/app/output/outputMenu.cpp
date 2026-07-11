/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "outputMenu.hpp"


OutputMenu::OutputMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
mainBackplate(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Getted data", "Полученные данные"}, 2, Height::Info),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
forceChart(_window, _X+0.015, _Y-0.2*_H, _W*0.85, _H*0.25, collectedData.getForces(), 0.0, 10.0, {"Force", "Сила"}),
tempertureChart(_window, _X+0.015, _Y+0.1*_H, _W*0.85, _H*0.25, collectedData.getTemperatures(), -40.0, 20.0, {"Temperature", "Температура"}),
saver(_window, _X, _Y+_H*0.45) {}

void OutputMenu::reset() {
    saver.reset();
}

bool OutputMenu::click(const Mouse mouse) {
    return false;
}

void OutputMenu::update() {

}

void OutputMenu::blit() const {
    mainBackplate.blit();
    title.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    forceChart.blit();
    tempertureChart.blit();
    saver.blit();
}
