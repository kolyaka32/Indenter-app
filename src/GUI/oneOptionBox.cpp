/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::OneOptionBox::OneOptionBox(const Window& _window, const TextArgument&& _arg, float _W, float _H,
    const LanguagedText&& _title, const LanguagedText&& _button) noexcept
: SubWindow(_window, _arg.X, _arg.Y, _W, _H),
title(_window, std::move(_title), {.X=_arg.X, .Y=_arg.Y-_H/4, .horAli=GUI::Aligment::Left, .height=Height::SubTitle, .frame=1}),
button(_window, std::move(_button), {.X=_arg.X, .Y=_arg.Y+_H/4}) {}

GUI::OneOptionBox::OneOptionBox(OneOptionBox&& _object) noexcept
: SubWindow(std::move(_object)),
title(std::move(_object.title)),
button(std::move(_object.button)) {}

GUI::Code GUI::OneOptionBox::click(const Mouse _mouse) {
    if (active) {
        // Returning to menu
        if (button.in(_mouse)) {
            return Button1;
        }
        return Some;
    }
    return None;
}

void GUI::OneOptionBox::move(float _X, float _Y) {
    SubWindow::move(_X, _Y);
    title.move(_X, _Y);
    button.move(_X, _Y);
}

void GUI::OneOptionBox::blit() const {
    if (active) {
        background.blit();
        title.blit();
        button.blit();
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
