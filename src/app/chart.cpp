/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "chart.hpp"


template <typename T>
Chart<T>::Chart(const Window& _window, float _X, float _Y, float _W, float _H, const std::vector<T>& _param,
    float _minValue, float _maxValue, const LanguagedText&& _title, SDL_Color _color)
: Template(_window),
minValue(_minValue),
maxValue(_maxValue),
drawRect({_X*_window.getWidth(), _Y*_window.getHeight(), _W*_window.getWidth(), _H*_window.getHeight()}),
param(_param),
color(_color),
title(_window, _X+_W/2, _Y-0.015, std::move(_title), 1) {}

template <typename T>
void Chart<T>::blit() const {
    // Draw background
    window.setDrawColor(WHITE);
    window.drawRect(drawRect);

    // Getting multipier for draw
    const float yMul = drawRect.h / (maxValue - minValue);
    const float xMul = drawRect.w / param.size();
    window.setDrawColor(color);
    for (int i=0; i < param.size(); ++i) {
        window.drawPoint(drawRect.x + i * xMul,
            drawRect.y + drawRect.h - param[i] * yMul);
    }

    // Draw title
    title.blit();
}
