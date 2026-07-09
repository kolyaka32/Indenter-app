/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


//
class ProgrammingMenu : GUI::Template {
private:
    /* data */

public:
    ProgrammingMenu(const Window& window, float X, float Y);
    void click(const Mouse mouse);
    void update();
    void blit() const override;
};
