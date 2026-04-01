/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "currentPort.hpp"


bool CurrentPort::openned = false;
int CurrentPort::selected = 0;
std::array<ComPort, 4> CurrentPort::ports {
    {{3}, {4}, {5}, {6}}
};

CurrentPort::CurrentPort(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
texts {
    {_window, _X+arrow, _Y,    {"Not selected", "Не выбран"}, Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y+_H, {ports[0].getName()},          Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y+_H, {ports[1].getName()},          Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y+_H, {ports[2].getName()},          Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y+_H, {ports[3].getName()},          Height::Main, BLACK, GUI::Aligment::Left},
},
height(_H) {
    background = {_window.getWidth()*_X, _window.getHeight()*(_Y-_H/2),
        _window.getWidth()*_W, _window.getHeight()*_H};
}

CurrentPort::~CurrentPort() {}

void CurrentPort::reset() {
    // Checking, if any ports avaliable
    openned = false;
    selected = 0;
    count = 1;

    for (int i=0; i < ports.size(); ++i) {
        ports[i].updateState();
        if (ports[i].isAvaliable()) {
            selected = i + 1;
            texts[i].move(0.0, height*count);
            count++;
        }
    }
}

void CurrentPort::update() {
    // Checking on changing variants
    for (int i=0; i < ports.size(); ++i) {
        // Check, if changed
        if (ports[i].updateState()) {
            if (ports[i].isAvaliable()) {
                // If adding
                count++;
                // Moving text itself to it position
                for (int j=0; j < i; ++j) {
                    if (ports[j].isAvaliable()) {
                        texts[i+1].move(0.0, height);
                    }
                }
                // If showing
                if (openned) {
                    background.h += height*window.getHeight();
                    // Moving all texts after it down
                    for (int j=i+1; j < ports.size(); ++j) {
                        if (ports[j].isAvaliable()) {
                            texts[j+1].move(0.0, height);
                        }
                    }
                } else {
                    // Moving all texts after it down
                    for (int j=i+1; j < ports.size(); ++j) {
                        if (ports[j].isAvaliable() && j+1 != selected) {
                            texts[j+1].move(0.0, height);
                        }
                    }
                }
            } else {
                // If removing line
                count--;
                // If showing in menu
                if (openned) {
                    background.h -= height*window.getHeight();
                    // Moving it back to start
                    for (int j=0; j < i; ++j) {
                        if (ports[j].isAvaliable()) {
                            // Moving current text to original position
                            texts[i+1].move(0.0, -height);
                        }
                    }
                    // Moving all texts after up
                    for (int j=i+1; j < ports.size(); ++j) {
                        if (ports[j].isAvaliable()) {
                            texts[j+1].move(0.0, -height);
                        }
                    }
                } else {
                    if (selected == i+1) {
                        // Moving back to place
                        texts[i+1].move(0.0, height);
                    } else {
                        // Moving back to place
                        for (int j=0; j < i; ++j) {
                            if (ports[j].isAvaliable()) {
                                texts[i+1].move(0.0, -height);
                            }
                        }
                    }
                    // Moving all texts after up
                    for (int j=i+1; j < ports.size(); ++j) {
                        if (ports[j].isAvaliable() && j+1 != selected) {
                            texts[j+1].move(0.0, -height);
                        }
                    }
                }
                // Checking, if remove current variant
                if (selected == i+1) {
                    // Resetting selected object
                    selected = 0;
                    // Resetting reading
                    serial.reset();
                }
            }
        }
    }
}

bool CurrentPort::click(const Mouse _mouse) {
    if (_mouse.in(background)) {
        if (openned) {
            // In openned menu - selecting variant and closing
            int newSelect = (_mouse.getY() - background.y) / (height*window.getHeight());
            if (newSelect) {
                // Finding position in list with this number
                int counted = 0;
                for (int i=0; i < ports.size(); ++i) {
                    if (ports[i].isAvaliable()) {
                        counted++;
                        if (newSelect == counted) {
                            selected = i + 1;
                            // Moving current variant to first pos
                            texts[selected].move(0.0, -height*counted);
                            break;
                        }
                    }
                }
            } else {
                selected = 0;
            }
            // Resetting flags
            openned = false;
            background.h = height * window.getHeight();
            // Appling action
            if (selected) {
                serial.tryConnectTo(ports[selected-1]);
            } else {
                serial.reset();
            }
            return true;
        } else {
            // Openning menu
            openned = true;
            // Swapping current text with first
            if (selected) {
                for (int i=0; i < selected; ++i) {
                    if (ports[i].isAvaliable()) {
                        texts[selected].move(0.0, height);
                    }
                }
            }
            background.h *= (count + 0.2f);
            return true;
        }
    } else {
        if (openned) {
            // If touch anywhere and openned - closing
            // Moving current variant to first pos
            if (selected) {
                for (int i=0; i < selected; ++i) {
                    if (ports[i].isAvaliable()) {
                        texts[selected].move(0.0, -height);
                    }
                }
            }
            // Resetting flags and size
            openned = false;
            background.h = height * window.getHeight();
            return true;
        }
    }
    return false;
}

void CurrentPort::blit() const {
    window.setDrawColor(WHITE);
    window.drawRect(background);

    // Check, if openned
    if (openned) {
        // Draw empty variant
        texts[0].blit();
        // Draw com variants
        for (int i=0; i < ports.size(); ++i) {
            if (ports[i].isAvaliable()) {
                texts[i+1].blit();
            }
        }
    } else {
        //
        texts[selected].blit();
    }
}
