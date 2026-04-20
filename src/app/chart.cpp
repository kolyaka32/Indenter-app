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
title(_window, _X+_W/2, _Y-0.018, std::move(_title), 1),
marks {
    {_window, _X-0.01f, _Y, {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right, _maxValue},
    {_window, _X-0.01f, _Y+_H/4, {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right, _maxValue*3/4+_minValue/4},
    {_window, _X-0.01f, _Y+_H/2, {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right, _maxValue/2+_minValue/2},
    {_window, _X-0.01f, _Y+_H*3/4, {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right, _maxValue/4+_minValue*3/4},
    {_window, _X-0.01f, _Y+_H, {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right, _minValue},
} {}

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

    // Draw marks
    marks[0].blit();
    marks[1].blit();
    marks[2].blit();
    marks[3].blit();
    marks[4].blit();
}
