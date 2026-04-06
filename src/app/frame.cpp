/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "frame.hpp"


ForceFrame::ForceFrame(Force _force)
: force(_force) {
    logger.additional("Force: %f", force);
}

ForceFrame::~ForceFrame() {}

void ForceFrame::blit(int _position, const Window& _window) const {
    _window.drawPoint(_position, force*10.0f + 100.0);
}


TemperatureFrame::TemperatureFrame(Temperature _data)
: temp(_data) {
    logger.additional("Temperature: %f", temp);
}

TemperatureFrame::~TemperatureFrame() {}

void TemperatureFrame::blit(int _position, const Window& _window) const {
    _window.drawPoint(_position, temp+200.0);
}
