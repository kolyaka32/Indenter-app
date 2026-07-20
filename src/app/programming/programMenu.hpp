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
    // Current executing programm
    static std::vector<Node*> nodes;
    static Node* currentNode;  // Current executing node to check
    // Runtime part
    bool wasWorking;
    Node* holdingNode;     // Node, that is holding by mouse or -1 if don't
    SDL_FPoint lastPos;    // Position, where it was holded last time
    LanguagedText filterText;  // Text for filter hint
    const SDL_DialogFileFilter filter;  // Filter for selection program file
    char saveLocation[100];    // Location with directory for save/load programs

    // Graphic part
    GUI::RoundedBackplate background;
    GUI::HighlightedStaticText title;
    SDL_FRect separateRect;
    NodeSelector selector;
    GUI::ImageButton startButton;
    GUI::ImageButton haltButton;
    GUI::ImageButton saveButton;
    GUI::ImageButton loadButton;
    GUI::InfoBox stoppedInfo;

protected:
    // Delete node with all connected
    void deleteNode(Node* node);

public:
    ProgramMenu(const Window& window, float X, float Y, float W, float H);
    void reset();

    // Interaction
    bool click(const Mouse mouse);
    void unclick(const Mouse mouse);
    void update(const Mouse mouse);
    void blit() const override;

    // Proceed action from get messages, start executing next command
    static void handlePos();
    static void handleReachPos();
    static void handleReachForce();
    // Return, if currently run any programs
    static bool isExecuting();
    static void stop();

    // Callback functions for save from dialog window
    static void SDLCALL save(void* userdata, const char* const* filelist, int filter);
    static void SDLCALL load(void* userdata, const char* const* filelist, int filter);
};
