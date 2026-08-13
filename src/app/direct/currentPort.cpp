/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "currentPort.hpp"
#include "../device.hpp"


bool CurrentPort::openned = false;
int CurrentPort::selected = 0;

CurrentPort::CurrentPort(const Window& _window, float _X, float _Y, float _W, float _H, float _thickness) noexcept
: Template(_window),
texts {
    {_window, _X-_W/2+arrow, _Y,    {"Not selected", "Не выбран"}, 1, GUI::Aligment::Left},
    {_window, _X-_W/2+arrow, _Y+_H, {comPorts[0].getName()},       1, GUI::Aligment::Left},
    {_window, _X-_W/2+arrow, _Y+_H, {comPorts[1].getName()},       1, GUI::Aligment::Left},
    {_window, _X-_W/2+arrow, _Y+_H, {comPorts[2].getName()},       1, GUI::Aligment::Left},
    {_window, _X-_W/2+arrow, _Y+_H, {comPorts[3].getName()},       1, GUI::Aligment::Left},
},
height(_H) {
    background = {_window.getWidth()*(_X-_W/2), _window.getHeight()*(_Y-_H/2),
        _window.getWidth()*_W, _window.getHeight()*_H};
    foreground = {_window.getWidth()*(_X-_W/2)+_thickness, _window.getHeight()*(_Y-_H/2)+_thickness,
        _window.getWidth()*_W-2*_thickness, _window.getHeight()*_H-2*_thickness};
}

void CurrentPort::reset() {
    // Checking, if any ports avaliable
    openned = false;
    selected = 0;
    count = 0;

    // Placing all variants
    for (int i=0; i < comPorts.size(); ++i) {
        comPorts[i].updateState();
        if (comPorts[i].isAvaliable()) {
            texts[i].move(0.0, height*count);
            count++;
        }
    }
    connectToFirst();

    // Counting first variant
    count++;
}

void CurrentPort::showPort(int _index) {
    // Moving text itself to it position
    for (int j=0; j < _index; ++j) {
        if (comPorts[j].isAvaliable()) {
            texts[_index+1].move(0.0, height);
        }
    }
    // If menu openned
    if (openned) {
        // Adding one height to each element
        background.h += height*window.getHeight();
        foreground.h += height*window.getHeight();
        // Moving all texts after it down
        for (int j=_index+1; j < comPorts.size(); ++j) {
            if (comPorts[j].isAvaliable()) {
                texts[j+1].move(0.0, height);
            }
        }
    } else {
        // Moving all texts after it down
        for (int j=_index+1; j < comPorts.size(); ++j) {
            if (comPorts[j].isAvaliable() && j+1 != selected) {
                texts[j+1].move(0.0, height);
            }
        }
    }
}

void CurrentPort::hidePort(int _index) {
    // If showing in menu
    if (openned) {
        background.h -= height*window.getHeight();
        foreground.h -= height*window.getHeight();
        // Moving it back to start
        for (int j=0; j < _index; ++j) {
            if (comPorts[j].isAvaliable()) {
                // Moving current text to original position
                texts[_index+1].move(0.0, -height);
            }
        }
        // Moving all texts after up
        for (int j=_index+1; j < comPorts.size(); ++j) {
            if (comPorts[j].isAvaliable()) {
                texts[j+1].move(0.0, -height);
            }
        }
        // Check, if remove current
        if (selected == _index+1) {
            // Resetting selected object
            selected = 0;
        }
    } else {
        if (selected == _index+1) {
            // Moving back to place
            texts[_index+1].move(0.0, height);
            // Resetting selected object
            selected = 0;
        } else {
            // Moving back to place
            for (int j=0; j < _index; ++j) {
                if (comPorts[j].isAvaliable()) {
                    texts[_index+1].move(0.0, -height);
                }
            }
        }
        // Moving all texts after it up
        for (int j=_index+1; j < comPorts.size(); ++j) {
            if (comPorts[j].isAvaliable() && j+1 != selected) {
                texts[j+1].move(0.0, -height);
            }
        }
    }
}

int CurrentPort::getPosition(const Mouse _mouse) {
    int newSelect = (_mouse.getY() - background.y) / (height*window.getHeight());
    if (newSelect) {
        for (int i=0; i < comPorts.size(); ++i) {
            if (comPorts[i].isAvaliable()) {
                newSelect--;
                if (newSelect == 0) {
                    // Returning current pos
                    return i + 1;
                }
            }
        }
    }
    return 0;
}

void CurrentPort::connectToFirst() {
    // Finding first avaliable variant
    for (int i=0; i < selected; ++i) {
        if (comPorts[i].isAvaliable()) {
            // Trying connected to it
            if (device.connectTo(comPorts[i])) {
                // Can't connect - return
                return;
            }
            // Selecting it
            selected = i+1;
            // Placing it at main place
            texts[selected].move(0.0, -height);
            return;
        }
    }
}

void CurrentPort::maximize() {
    openned = true;
    for (int i=0; i < comPorts.size(); ++i) {
        if (comPorts[i].isAvaliable()) {
            background.h += height * window.getHeight();
            foreground.h += height * window.getHeight();
        }
    }
    background.h += 0.2f * height * window.getHeight();
    foreground.h += 0.2f * height * window.getHeight();
}

void CurrentPort::minimize() {
    openned = false;
    for (int i=0; i < comPorts.size(); ++i) {
        if (comPorts[i].isAvaliable()) {
            background.h -= height * window.getHeight();
            foreground.h -= height * window.getHeight();
        }
    }
    background.h -= 0.2f * height * window.getHeight();
    foreground.h -= 0.2f * height * window.getHeight();
}

void CurrentPort::moveSelectedUp() {
    for (int i=0; i < selected; ++i) {
        if (comPorts[i].isAvaliable()) {
            texts[selected].move(0.0, height);
        }
    }
}

void CurrentPort::moveSelectedDown() {
    for (int i=0; i < selected; ++i) {
        if (comPorts[i].isAvaliable()) {
            texts[selected].move(0.0, -height);
        }
    }
}

void CurrentPort::update() {
    // Checking on changing variants
    for (int i=0; i < comPorts.size(); ++i) {
        if (comPorts[i].updateState()) {
            // If port change state
            if (comPorts[i].isAvaliable()) {
                // If connect new
                count++;
                showPort(i);
            } else {
                // If disconnecting
                count--;
                hidePort(i);
                // Checking, if remove current
                if (selected == i+1) {
                    device.disconnect();
                }
            }
        }
    }
}

bool CurrentPort::click(const Mouse _mouse) {
    if (_mouse.in(background)) {
        if (openned) {
            // In openned menu - selecting variant and closing
            selected = getPosition(_mouse);
            // Appling action
            if (selected) {
                // Connecting to new selected
                if (device.connectTo(comPorts[selected-1])) {
                    // Couldn't connect
                    selected = 0;
                }
            } else {
                // Disconnecting (if first variant)
                device.disconnect();
            }
            moveSelectedDown();
            minimize();
            return true;
        } else {
            // Openning menu
            moveSelectedUp();
            maximize();
            return true;
        }
    } else {
        if (openned) {
            // If touch anywhere - close
            moveSelectedDown();
            minimize();
            return true;
        }
    }
    return false;
}

bool CurrentPort::press(SDL_Keycode _key) {
    if (openned) {
        if (_key == SDLK_ESCAPE) {
            moveSelectedDown();
            minimize();
        }
        return true;
    }
    return false;
}

void CurrentPort::blit() const {
    window.setDrawColor(BLACK);
    window.drawRect(background);

    window.setDrawColor(GREY);
    window.drawRect(foreground);

    // Check, if openned
    if (openned) {
        // Draw empty variant
        texts[0].blit();
        // Draw com variants
        for (int i=0; i < comPorts.size(); ++i) {
            if (comPorts[i].isAvaliable()) {
                texts[i+1].blit();
            }
        }
    } else {
        // Blit only selected text, placed at main part
        texts[selected].blit();
    }
}
