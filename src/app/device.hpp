/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"
#include "../serial/serial.hpp"


// Class for interact with device and store it state
class Device {
 public:
    Device();
    ~Device();

    // Posible states of device
    enum States {
        NotConnected,  // Device not connected (or selected)
        Waiting,       // Waiting for command
        IdleSpeed,     // Going to sample at full speed
        MainSpeed,     // Measuring sample at low speed
    };

    void disconnect();
    void connectTo(const ComPort port);
    void start();
    void stop();

    // Cycle interact
    void update();

    States state = NotConnected;
};

// Object store state of device and interact with him
extern Device device;
