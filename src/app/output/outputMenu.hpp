/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../app/collectedData.hpp"
#include "chart.cpp"
#include "saver.hpp"


// Object for interact with collected data (show and save)
class OutputMenu : GUI::Template {
private:
    GUI::RoundedBackplate mainBackplate;
    GUI::HighlightedStaticText title;
    SDL_FRect separateRect;
    Chart<Force> forceChart;
    Chart<Temperature> tempertureChart;
    Saver saver;

public:
    OutputMenu(const Window& window, float X, float Y, float W, float H);
    void reset();

    bool click(const Mouse mouse);
    void update();
    void blit() const override;
};
