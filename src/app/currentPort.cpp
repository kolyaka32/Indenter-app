/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "currentPort.hpp"


bool CurrentPort::openned = false;
int CurrentPort::selected = 0;
std::array<bool, 4> CurrentPort::avaliableTexts {};


CurrentPort::CurrentPort(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
texts {
    {_window, _X+arrow, _Y, {"Not selected", "Не выбран"}, Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y, {serial.ports[0].name},        Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y, {serial.ports[1].name},        Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y, {serial.ports[2].name},        Height::Main, BLACK, GUI::Aligment::Left},
    {_window, _X+arrow, _Y, {serial.ports[3].name},        Height::Main, BLACK, GUI::Aligment::Left},
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
    serial.updateConnections();
    int count = 1;

    for (int i=0; i < serial.ports.size(); ++i) {
        avaliableTexts[i] = serial.ports[i].avaliable;
        if (avaliableTexts[i]) {
            selected = i + 1;
            texts[i].move(0.0, height*count);
            count++;
        }
    }
}

void CurrentPort::update() {
    // Checking on changing variants
    for (int i=0; i < serial.ports.size(); ++i) {
        if (serial.ports[i].avaliable != avaliableTexts[i]) {
            avaliableTexts[i] = serial.ports[i].avaliable;
            if (avaliableTexts[i]) {
                // If adding new line
                if (openned) {
                    //
                    background.h += height*window.getHeight();
                    // Counting up to this showing texts
                    texts[i+1].move(0.0, height);
                    for (int j=0; j < i; ++j) {
                        if (avaliableTexts[i]) {
                            texts[i+1].move(0.0, height);
                        }
                    }
                    // Moving all texts after down
                    for (int j=i+1; j < serial.ports.size(); ++j) {
                        if (avaliableTexts[i]) {
                            texts[j+1].move(0.0, height);
                        }
                    }
                }
            } else {
                // If removing line
                if (openned) {
                    //
                    background.h -= height*window.getHeight();
                    // Counting up to this showing texts
                    texts[i+1].move(0.0, -height);
                    for (int j=0; j < i; ++j) {
                        if (avaliableTexts[i]) {
                            // Moving current text to original position
                            texts[i+1].move(0.0, -height);
                        }
                    }
                    // Moving all texts after up
                    for (int j=i+1; j < serial.ports.size(); ++j) {
                        if (avaliableTexts[i]) {
                            texts[j+1].move(0.0, -height);
                        }
                    }
                    // Checking, if remove current variant
                    if (selected = i+1) {
                        // Resetting selected object
                        selected = 0;

                        // Resetting reading
                        resetPort();
                    }
                } else {
                    // Checking, if remove current variant
                    if (selected = i+1) {
                        // Moving selected text back to it pos
                        texts[selected].move(0.0, selected*height);

                        // Resetting selected object
                        selected = 0;

                        // Resetting reading
                        resetPort();
                    }
                }
            }
        }
    }
}

bool CurrentPort::click(const Mouse _mouse) {
    if (_mouse.in(background)) {
        if (openned) {
            // In openned menu - selecting variant and closing
            openned = false;
            background.h = height * window.getHeight();
            // Moving previous variant back
            for (int i=0; i < selected; ++i) {
                if (avaliableTexts[i]) {
                    texts[selected].move(0.0, height);
                }
            }
            // Selecting variant
            selected = (_mouse.getY() - background.y) / background.h;
            selectPort(selected);
            return true;
        } else {
            // Openning menu
            openned = true;
            // Counting avaliable texts
            float count = 1.2;  // Non variant + 0.1 for understanding openning
            for (int i=0; i < avaliableTexts.size(); ++i) {
                if (avaliableTexts[i]) {
                    count += 1.0;
                }
            }
            // Swapping current text with first
            for (int i=0; i < selected; ++i) {
                if (avaliableTexts[i]) {
                    texts[selected].move(0.0, height);
                }
            }
            background.h *= count;
            return true;
        }
    } else {
        if (openned) {
            // If touch anywhere and openned - closing
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
        for (int i=0; i < serial.ports.size(); ++i) {
            if (avaliableTexts[i]) {
                texts[i+1].blit();
            }
        }
    } else {
        //
        texts[selected].blit();
    }
}

void CurrentPort::selectPort(int _port) {
    // !
    if (_port) {
        // Selecting new port
    } else {
        resetPort();
    }
}

void CurrentPort::resetPort() {
    // !
}
