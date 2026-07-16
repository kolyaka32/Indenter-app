/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../collectedData.hpp"
#include "chart.cpp"


// Object for interact with collected data (show and save)
class OutputMenu : GUI::Template {
private:
    LanguagedText filterText;  // Text for filter hint
    const SDL_DialogFileFilter filter;  // Filter for selection data file
    char saveLocation[100];    // Location with directory for save/load datas

    GUI::RoundedBackplate mainBackplate;
    GUI::HighlightedStaticText title;
    SDL_FRect separateRect;
    // Getted graphs
    Chart<Position, Force> forceChart;
    Chart<Position, Temperature> tempertureChart;
    // Save function
    GUI::DynamicText counterText;
    GUI::HighlightedStaticText notSavedText;
    GUI::TextButton saveButton;

public:
    OutputMenu(const Window& window, float X, float Y, float W, float H);
    void reset();

    bool click(const Mouse mouse);
    void update();
    void blit() const override;

    static SDLCALL void save(void* userdata, const char* const* filelist, int filter);
};
