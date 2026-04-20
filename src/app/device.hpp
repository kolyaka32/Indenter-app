/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


// Class for interact with device and store it state
class Device {
private:
    /* data */

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
    void connect();

    // Cycle interact
    void update();

    States state;
};

// Object store state of device and interact with him
extern Device device;
