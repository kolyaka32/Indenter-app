/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "chart.hpp"


template <typename xAxis, typename yAxis>
Chart<xAxis, yAxis>::Chart(const Window& _window, float _X, float _Y, float _W, float _H,
    const BoundedArray<xAxis>& _pos, const BoundedArray<yAxis>& _value, const LanguagedText&& _title, SDL_Color _color)
: Template(_window),
pos(_pos),
value(_value),
drawRect({(_X-_W/2)*_window.getWidth(), (_Y-_H/2)*_window.getHeight(), _W*_window.getWidth(), _H*_window.getHeight()}),
color(_color),
title(_window, _X, _Y-0.018-_H/2, std::move(_title), 1),
marks {
    {_window, _X-0.01f-_W/2, _Y-_H/2,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.01f-_W/2, _Y-_H/4,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.01f-_W/2, _Y,       {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.01f-_W/2, _Y+_H/4,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.01f-_W/2, _Y+_H/2,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
} {
    update();
}

template <typename xAxis, typename yAxis>
void Chart<xAxis, yAxis>::update() {
    marks[0].setValues(value.max());
    marks[1].setValues(value.max()*3/4+value.min()/4);
    marks[2].setValues(value.max()/2+  value.min()/2);
    marks[3].setValues(value.max()/4+  value.min()*3/4);
    marks[4].setValues(value.min());
}

template <typename xAxis, typename yAxis>
void Chart<xAxis, yAxis>::blit() const {
    // Draw background
    window.setDrawColor(WHITE);
    window.drawRect(drawRect);

    // Getting multipier for draw
    const float yMul = drawRect.h / (value.max() - value.min());
    const float xMul = drawRect.w / (pos.max() - pos.min());
    window.setDrawColor(color);
    for (int i=0; i < value.size(); ++i) {
        window.drawPoint(drawRect.x + pos[i] * xMul,
            drawRect.y + drawRect.h - value[i] * yMul);
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
