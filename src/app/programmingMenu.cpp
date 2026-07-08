/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "programmingMenu.hpp"


ProgrammingMenu::ProgrammingMenu(const Window& _window, float X, float Y)
: Template(_window) {}

void ProgrammingMenu::click(const Mouse mouse) {
    
}

void ProgrammingMenu::update() {

}

void ProgrammingMenu::blit() const  {
    SDL_Vertex points[] = {
        {},
    };
    //window.render  // ! Required to port render geometry from main game engine part
}
