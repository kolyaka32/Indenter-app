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
yMarks {
    {_window, _X-0.01f-_W/2, _Y-_H/2,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.01f-_W/2, _Y-_H/4,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.01f-_W/2, _Y,       {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.01f-_W/2, _Y+_H/4,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.01f-_W/2, _Y+_H/2,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
},
xMarks {
    {_window, _X-_W/2, _Y+_H/2+0.02f,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Left},
    {_window, _X+_W/2, _Y+_H/2+0.02f,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
} {
    update();
}

template <typename xAxis, typename yAxis>
void Chart<xAxis, yAxis>::update() {
    yMarks[0].setValues(value.max());
    yMarks[1].setValues(value.max()*3/4+value.min()/4);
    yMarks[2].setValues(value.max()/2+  value.min()/2);
    yMarks[3].setValues(value.max()/4+  value.min()*3/4);
    yMarks[4].setValues(value.min());
    xMarks[0].setValues(pos.min());
    xMarks[1].setValues(pos.max());
}

template <typename xAxis, typename yAxis>
void Chart<xAxis, yAxis>::blit() const {
    // Draw background
    window.setDrawColor(WHITE);
    window.drawRect(drawRect);

    // Draw title
    title.blit();

    // Draw marks
    yMarks[0].blit();
    yMarks[1].blit();
    yMarks[2].blit();
    yMarks[3].blit();
    yMarks[4].blit();
    xMarks[0].blit();
    xMarks[1].blit();

    // Getting multipier for draw
    const float yMul = drawRect.h / (value.max() - value.min());
    const float xMul = drawRect.w / (pos.max() - pos.min());
    // Draw chart itself
    window.setDrawColor(color);
    for (int i=0; i < value.size(); ++i) {
        window.drawPoint(drawRect.x + (pos[i] - pos.min()) * xMul,
            drawRect.y + drawRect.h - (value[i] - value.min()) * yMul);
    }
}
