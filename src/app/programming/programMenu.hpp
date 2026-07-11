/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include <array>
#include "node.hpp"
#include "nodeSelector.hpp"


// Menu for create and edit of programs on own sratch-like visual language
class ProgramMenu : GUI::Template {
private:
    // Current executing programm
    static std::vector<Node*> nodes;
    unsigned currentNode;  // Current executing node to check
    int holdingNode;       // Node, that is holding by mouse or -1 if don't
    SDL_FPoint lastPos;    // Position, where it was holded last time
    LanguagedText filterText;  // Text for filter hint
    const SDL_DialogFileFilter filter;  // Filter for selection program file
    char saveLocation[100];    // Location with directory for save/load programs

    // Graphic part
    GUI::RoundedBackplate background;
    GUI::HighlightedStaticText title;
    SDL_FRect separateRect;
    GUI::ImageButton startButton;
    GUI::ImageButton haltButton;
    GUI::ImageButton saveButton;
    GUI::ImageButton loadButton;
    NodeSelector selector;

public:
    ProgramMenu(const Window& window, float X, float Y, float W, float H);
    void reset();

    // Interaction
    bool click(const Mouse mouse);
    void update();
    void blit() const override;

    // Callback functions for save from dialog window
    static void SDLCALL save(void* userdata, const char* const* filelist, int filter);
    static void SDLCALL load(void* userdata, const char* const* filelist, int filter);
};
