/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Object for menu for save data
class Saver {
protected:
    // Flag of openning current menu
    static bool active;

    // Always visibal graphical part
    GUI::HighlightedStaticText notSavedText;  // Text, that current data not saved
    GUI::TextButton saveButton;               // Button for openning current menu
    GUI::InfoBox savedInfo;                   // Additional info of correct file save

    // Hidden menu graphical part
    GUI::RoundedBackplate backplate;       // Backplate for better visability
    GUI::HighlightedStaticText menuTitle;  // Title for menu
    GUI::TypeBox<20> fileNameTypeBox;      // Typebox for entering file name to save
    GUI::TextButton menuSaveButton;        // Button for trying to save current data
    GUI::TextButton menuCloseButton;       // Button for close this menu
    GUI::TwoOptionBox rewriteOptions;      // Option box for check, if want to rewrite file

public:
    Saver(const Window& window);
    void reset();

    bool click(const Mouse mouse);
    void unclick();
    bool type(SDL_Keycode code);
    void inputText(const char* text);
    void update();
    void blit() const;
};
