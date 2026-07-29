/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::InfoBox::InfoBox(const Window& _window, float _X, float _Y, const LanguagedText&& _texts,
    unsigned _decay, Aligment _aligment, float _height, Color _color) noexcept
: HighlightedStaticText(_window, _X, _Y, std::move(_texts), 2, _aligment, _height, _color),
decayTime(_decay) {
    // Resetting transperance
    SDL_SetTextureAlphaMod(texture, 0.0);
}

GUI::InfoBox::InfoBox(InfoBox&& _object) noexcept
: HighlightedStaticText(std::move(_object)),
decayTime(_object.decayTime),
endTime(_object.endTime) {
    // First update to correct showing
    update();
}

void GUI::InfoBox::update() {
    if (endTime >= getTime()) {
        // Setting text to be less and less visible
        SDL_SetTextureAlphaModFloat(texture, (float)(endTime - getTime()) / decayTime);
    } else {
        // Fully transperent
        SDL_SetTextureAlphaModFloat(texture, 0.0);
    }
}

void GUI::InfoBox::reset() {
    endTime = getTime() + decayTime;
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
