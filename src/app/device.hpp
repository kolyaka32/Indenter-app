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
        NotConnected,   // Device not connected (or selected)
        NotResponding,  // Device connected, but don't send anything
        Waiting,        // Waiting for command
        Working,       // Going to sample at full speed
    };

    // Codes of messages, recieving from controller
    enum class Get {
        None,    // Nothing, for apply connection
        Packet,  // One frame with new sensors values
        ReachPos,  // Signal, that reach setted position
        ReachForce,  // Signal, that reach setted force
    };

    // Codes of messages, sending to controller
    enum class Send {
        None,
        Stop,
        SetMoveUp,
        SetMoveDown,
        SetRunUp,
        SetRunDown,
        ReachPos,
        ReachForce,
    };

    void disconnect();
    void connectTo(const ComPort port);

    // Cycle interact
    void checkRecieve();
    void sendStop();
    void sendMoveUp();
    void sendMoveDown();
    void sendRunUp();
    void sendRunDown();
    void sendReachPos(int pos);
    void sendReachForce();
    bool isConnected() const;

    States state = NotConnected;
    timer lastRecieve = 0;
    // How long could don't messages until set to not responding
    const timer exceedWait = 1000;
};

// Object store state of device and interact with him
extern Device device;
