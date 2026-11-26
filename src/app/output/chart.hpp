/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <vector>
#include "../../GUI/interface.hpp"
#include "boundedArray.hpp"


// Class for draw graphic single parameter
class Chart : GUI::Template {
private:
    // Drawing value
    const BoundedArray& pos;
    const BoundedArray& val;

    // Graphic part
    const SDL_FRect drawRect;
    const SDL_Color color;
    GUI::StaticText title;
    GUI::DynamicText yMarks[5];
    GUI::DynamicText xMarks[2];

public:
    Chart(const Window& window, float X, float Y, float W, float H, const BoundedArray& pos,
        const BoundedArray& value, const LanguagedText&& title, SDL_Color color = BLACK);

    void update();
    void blit() const;
};
