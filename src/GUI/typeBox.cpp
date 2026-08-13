/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


template <unsigned bufferSize>
GUI::TypeBox<bufferSize>::TypeBox(const Window& _window, float _X, float _Y, const char *_startText,
    Aligment _aligment, float _height, unsigned _frameWidth, Color _textColor) noexcept
: TypeField<bufferSize>(_window, _X, _Y, _startText, _aligment, _height, _textColor),
backplate(_window, {_X*_window.getWidth()-(13*bufferSize-2)*(int)_aligment/2-4,
    _Y*_window.getHeight()-_height*0.85f, 13.0f * bufferSize+4, _height * 1.8f}, 2, WHITE, BLACK) {}

template <unsigned bufferSize>
GUI::TypeBox<bufferSize>::TypeBox(TypeBox&& _object) noexcept
: TypeField<bufferSize>(std::move(_object)),
backplate(std::move(_object.backplate)) {}

template <unsigned bufferSize>
void GUI::TypeBox<bufferSize>::move(float _X, float _Y) {
    TypeField<bufferSize>::move(_X, _Y);
    backplate.move(_X, _Y);
}

template <unsigned bufferSize>
void GUI::TypeBox<bufferSize>::blit() const {
    // Rendering background picture for better typing
    backplate.blit();

    // Rendering text
    TypeField<bufferSize>::blit();
}

template <unsigned bufferSize>
bool GUI::TypeBox<bufferSize>::in(const Mouse _mouse) const {
    return backplate.in(_mouse);
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
