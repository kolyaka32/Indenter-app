/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::Checkbox::Checkbox(const Window& _window, bool& _state, SDL_FRect _rect)
: TextureTemplate(_window, _rect, _window.createTexture(_rect.w, _rect.h)),
state(_state),
backplate(_window, _rect, 3.0, WHITE) {
    SDL_FColor color = {0.0, 0.0, 0.0, 1.0};  // Black
    SDL_Vertex vertex[] = {
        {{rect.w*0.13f, rect.h*0.65f}, color},
        {{rect.w*0.20f, rect.h*0.55f}, color},
        {{rect.w*0.35f, rect.h*0.88f}, color},
        {{rect.w*0.35f, rect.h*0.75f}, color},
        {{rect.w*0.90f, rect.h*0.25f}, color},
        {{rect.w*0.80f, rect.h*0.15f}, color},
    };
    int order[] = {0, 1, 2,   1, 2, 3,   2, 3, 4,   3, 4, 5};
    window.setRenderTarget(texture);
    window.drawGeometry(vertex, SDL_arraysize(vertex), order, SDL_arraysize(order));
    window.resetRenderTarget();
}

GUI::Checkbox::Checkbox(const Window& _window, bool& _state, float _X, float _Y, float _W)
: Checkbox(_window, _state, {(_X-_W/2)*_window.getWidth(), _Y*_window.getHeight()-_W/2*_window.getWidth(),
    _W*_window.getWidth(), _W*_window.getWidth()}) {}

GUI::Checkbox::Checkbox(Checkbox&& _object) noexcept
: TextureTemplate(std::move(_object)),
state(_object.state),
backplate(std::move(_object.backplate)) {}

GUI::Checkbox::~Checkbox() noexcept {
    if (texture) {
        window.destroy(texture);
    }
}

GUI::Code GUI::Checkbox::click(const Mouse _mouse) {
    if (backplate.in(_mouse)) {
        state ^= true;
        return Some;
    }
    return None;
}

void GUI::Checkbox::move(float _X, float _Y) {
    backplate.move(_X, _Y);
    TextureTemplate::move(_X, _Y);
}

void GUI::Checkbox::blit() const {
    backplate.blit();
    if (state) {
        window.blit(texture, rect);
    }
}
