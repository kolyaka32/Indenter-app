/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


//
class ProgrammingMenu : GUI::Template {
private:
    //const SDL_FColor orange = {1.0, 0.6, 0.1, 1.0};  // Orange
    static const unsigned number = 14;
    SDL_Vertex points[number];

public:
    ProgrammingMenu(const Window& window, float X, float Y, float H, SDL_FColor color);
    bool click(const Mouse mouse);
    void update();
    void blit() const override;
};
