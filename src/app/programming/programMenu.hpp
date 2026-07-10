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
    std::vector<Node*> nodes;
    unsigned currentNode;  // Current executing node to check
    int holdingNode;       // Node, that is holding by mouse or -1 if don't
    SDL_FPoint lastPos;    // Position, where it was holded last time

    GUI::RectBackplate background;
    // Control part
    GUI::ImageButton startPauseButton;
    GUI::ImageButton haltButton;

    NodeSelector selector;

public:
    ProgramMenu(const Window& window, float X, float Y, float W, float H);
    void reset();

    // Interaction
    void click(const Mouse mouse);
    void update();
    void blit() const override;

    //
    void save();
    void load();
};
