/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "collectedData.hpp"
#include "chart.hpp"


// Object for interact with collected data (show and save)
class OutputMenu : GUI::Template {
private:
    // Graphical part
    GUI::RoundedBackplate mainBackplate;
    GUI::StaticText title;
    SDL_FRect separateRect;
    // Getted data
    Chart forceChart;
    Chart tempertureChart;
    GUI::DynamicText forceText;
    GUI::DynamicText tempText;
    GUI::DynamicText counterText;
    // Set null part
    GUI::StaticText setForceNullText;
    GUI::TextButton setForceNullAsLastButton;
    GUI::TextButton setForceNullAsAvarButton;
    GUI::TextButton setPosNullButton;
    // Save function
    GUI::StaticText notSavedText;
    GUI::TextButton saveButton;
    GUI::TextButton folderButton;

    // Save system  // ! Rework to own class
    LanguagedText filterText;  // Text for filter hint
    const SDL_DialogFileFilter filter;  // Filter for selection data file
    char saveLocation[100];    // Location with directory for save/load datas
    static char* saveName;

public:
    OutputMenu(const Window& window, float X, float Y, float W, float H);
    void reset();

    bool click(const Mouse mouse);
    void update();
    void blit() const override;

    static SDLCALL void save(void* userdata, const char* const* filelist, int filter);
};
