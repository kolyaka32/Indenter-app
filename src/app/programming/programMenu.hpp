/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "nodeSelector.hpp"


// Menu for create and edit of programs on own sratch-like visual language
class ProgramMenu : GUI::Template {
private:
    // Runtime part
    Node* holdingNode;        // Node, that is holding by mouse or nullptr if don't
    SubNode* holdingSubNode;  // Special node, refer as argument for other nodes
    SDL_FPoint lastPos;       // Position, where it was holded last time
    // Save/load
    static char* saveName;
    static char* loadName;
    LanguagedText filterText;  // Text for filter hint
    const SDL_DialogFileFilter filter;  // Filter for selection program file
    char saveLocation[100];    // Location with directory for save/load programs
    char autosaveFile[100];    // File for auto save/load

    // Graphic part
    GUI::RoundedBackplate background;
    GUI::HighlightedStaticText title;
    SDL_FRect separateRect;
    NodeSelector selector;
    GUI::ImageButton newButton;
    GUI::TwoOptionBox clearOption;
    GUI::ImageButton saveButton;
    GUI::ImageButton loadButton;
    GUI::ImageButton startButton;
    GUI::ImageButton haltButton;
    GUI::InfoBox netConnectedInfo;
    GUI::InfoBox stoppedInfo;

public:
    ProgramMenu(const Window& window, float X, float Y, float W, float H);
    ~ProgramMenu();
    void reset();

    // Interaction
    bool click(const Mouse mouse);
    void unclick(const Mouse mouse);
    void type(SDL_Keycode code);
    void writeString(const char* str);
    void update(const Mouse mouse);
    void blit() const override;

    // Current executing programm
    static Program program;

    // Callback functions for save from dialog window
    static void SDLCALL save(void* userdata, const char* const* filelist, int filter);
    static void SDLCALL load(void* userdata, const char* const* filelist, int filter);
};
