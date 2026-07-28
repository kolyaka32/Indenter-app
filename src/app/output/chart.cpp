/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "chart.hpp"


template <typename xAxis, typename yAxis>
Chart<xAxis, yAxis>::Chart(const Window& _window, float _X, float _Y, float _W, float _H,
    const BoundedArray<xAxis>& _pos, const BoundedArray<yAxis>& _val, const LanguagedText&& _title, SDL_Color _color)
: Template(_window),
pos(_pos),
val(_val),
drawRect({(_X-_W/2)*_window.getWidth(), (_Y-_H/2)*_window.getHeight(), _W*_window.getWidth(), _H*_window.getHeight()}),
color(_color),
title(_window, _X, _Y-0.018-_H/2, std::move(_title), 1),
yMarks {
    {_window, _X-0.005f-_W/2, _Y-_H/2,  {"%.2f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.005f-_W/2, _Y-_H/4,  {"%.2f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.005f-_W/2, _Y,       {"%.2f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.005f-_W/2, _Y+_H/4,  {"%.2f"}, Height::Medium, BLACK, GUI::Aligment::Right},
    {_window, _X-0.005f-_W/2, _Y+_H/2,  {"%.2f"}, Height::Medium, BLACK, GUI::Aligment::Right},
},
xMarks {
    {_window, _X-_W/2, _Y+_H/2+0.02f,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Left},
    {_window, _X+_W/2, _Y+_H/2+0.02f,  {"%.1f"}, Height::Medium, BLACK, GUI::Aligment::Right},
} {
    update();
}

template <typename xAxis, typename yAxis>
void Chart<xAxis, yAxis>::update() {
    yMarks[0].setValues(val.max());
    yMarks[1].setValues(val.max()*3/4+val.min()/4);
    yMarks[2].setValues(val.max()/2+  val.min()/2);
    yMarks[3].setValues(val.max()/4+  val.min()*3/4);
    yMarks[4].setValues(val.min());
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
    const float xMul = drawRect.w / (pos.max() - pos.min()) * 0.94; 
    const float yMul = drawRect.h / (val.max() - val.min()) * 0.94;
    const float xStart = drawRect.x + drawRect.w * 0.02;
    const float yStart = drawRect.y + drawRect.h - drawRect.w * 0.02;
    // Draw chart itself
    window.setDrawColor(color);
    if (pos.size()) {
        float prevPosition = drawRect.x + (pos[0] - pos.min()) * xMul;
        float prevValue = yStart - (val[0] - val.min()) * yMul;
        for (int i=1; i < val.size(); ++i) {
            float position = xStart + (pos[i] - pos.min()) * xMul;
            float value = yStart - (val[i] - val.min()) * yMul;
            window.drawLine(prevPosition, prevValue, position, value);
            prevPosition = position;
            prevValue = value;
        }
    }
}
