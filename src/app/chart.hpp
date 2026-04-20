/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <vector>
#include "../GUI/interface.hpp"


// Class for draw graphic single parameter
template <typename T>
class Chart : GUI::Template {
private:
    const float maxValue, minValue;
    const SDL_FRect drawRect;
    const SDL_Color color;
    const std::vector<T>& param;
    GUI::HighlightedStaticText title;

public:
    Chart(const Window& window, float X, float Y, float W, float H, const std::vector<T>& param,
        float minValue, float maxValue, const LanguagedText&& title, SDL_Color color = BLACK);

    void blit() const;
};
