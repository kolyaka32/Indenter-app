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
        Working,        // Going to sample at full speed
    };

    // Main device state
    States state = NotConnected;

    // Codes of messages, recieving from controller
    enum class Get {
        None,        // Nothing, for apply connection
        // Current state
        Waiting,     // Currently waiting for command
        Working,     // Currently moving
        // 
        Packet,      // One frame with new sensors values
        // Complete task
        Position,    // Signal with current position
        ReachPos,    // Signal, that reach setted position
        ReachForce,  // Signal, that reach setted force
    };

    // Codes of messages, sending to controller
    enum class Send {
        None,
        GetPos,  // !
        ReachForce,  // ! Required realisation
        LostForce,
        SetWorkUp,
        SetWorkDown,
        SetIdleUp,
        SetIdleDown,
        SetStepUp,
        SetStepDown, // ! Required realisation 
        SetMoveTo,   // !
        Stop,
    };

    void disconnect();
    void connectTo(const ComPort port);

    // Posible sendings
    // Immidiate stop
    void sendStop();
    // Working speed infinite movement
    void sendMoveUp();
    void sendMoveDown();
    // Idle speed infinite movement
    void sendIdleUp();
    void sendIdleDown();
    // Relative movement by step count
    void sendStepUp(int steps);
    void sendStepDown(int steps);
    // Absolute movement to pos (should by get only from get position)
    void sendMoveToPos(int pos);
    // Sensors
    void sendReachForce();
    void sendLoseForce();
    void sendGetPos();

    // Cycle update
    void checkRecieve();
    bool isConnected() const;

 private:
    // How long could don't messages until set to not responding
    timer lastRecieve = 0;
    const timer exceedWait = 1000;
};

// Object store state of device and interact with him
extern Device device;
