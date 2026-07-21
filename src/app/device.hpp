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
        // Pre work
        NotConnected,   // Device not connected (or selected)
        // Unknown
        NotResponding,  // Device connected, but don't send anything
        // Normal work
        Waiting,        // Waiting for command
        Working,        // Going to sample at full speed
    };
    // Main device state
    States state = NotConnected;

    void disconnect();
    bool connectTo(const ComPort port);

    // Posible sendings
    // Codes of messages, sending to controller (sorted by importance)
    enum class Send {
        None,
        // Getters
        GetPos,       // Ask current position
        // Set sensors
        ReachForce,   // Send signal, when exceed setted force
        LowerForce,   // Send signal, when get lower setted force
        // Movement
        SetWorkUp,    // Start moving up with working (slow) speed
        SetWorkDown,  // Start moving down with working (slow) speed
        SetIdleUp,    // Start moving up with idle (fast) speed
        SetIdleDown,  // Start moving down with idle (fast) speed
        SetStepUp,    // Move up by specified number of steps
        SetStepDown,  // Move down by specified number of steps
        SetMoveTo,    // Move to setted position
        // Stop
        Stop,         // Stop all movement
    };
    // Immidiate stop
    void sendStop();
    // Working speed infinite movement
    void sendMoveUp();
    void sendMoveDown();
    // Idle speed infinite movement
    void sendIdleUp();
    void sendIdleDown();
    // Relative movement by step count
    void sendStepUp(float distance);
    void sendStepDown(float distance);
    // Absolute movement to pos (should by get only from get position)
    void sendMoveToPos(int pos);
    // Sensors
    void sendReachForce();
    void sendLoseForce();
    void sendGetPos();

    // Receiving
    // Codes of messages, recieving from controller (sorted by importance)
    enum class Get {
        None,        // Nothing, for apply connection
        // Current state
        Waiting,     // Currently waiting for command
        Working,     // Currently moving
        // New measures
        Packet,      // One frame with new [position], [force] and [temperature]
        // Complete task
        Position,    // Signal with current [position]
        ReachPos,    // Signal, that reach setted position
        ReachForce,  // Signal, that reach setted force
    };
    void checkRecieve();
    bool isConnected() const;

 private:
    // How long could don't messages until set to not responding
    timer lastRecieve = 0;
    const timer exceedWait = 1000;
};

// Object store state of device and interact with him
extern Device device;
