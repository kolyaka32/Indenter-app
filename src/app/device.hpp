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
    typedef Uint16 Type;
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
        ReachForce,   // Send to said, when exceed setted [force]
        LowerForce,   // Send to send, when get lower setted [force]
        // Movement
        SetMoveUp,    // Start move up with [speed]
        SetMoveDown,  // Start move down with [speed]
        SetStepUp,    // Move up with [speed] by specified number of [steps]
        SetStepDown,  // Move down with [speed] by specified number of [steps]
        SetMoveTo,    // Move with [speed] to setted [position]
        // Stop
        SetStop,      // Stop movement
    };
    // Immidiate stop
    void sendStop();
    // Working speed infinite movement
    void sendMoveUp(Uint16 speed);
    void sendMoveDown(Uint16 speed);
    // Relative movement by step count
    void sendStepUp(Uint16 speed, float distance);
    void sendStepDown(Uint16 speed, float distance);
    // Absolute movement to pos (should by get only from get position)
    void sendMoveToPos(Uint16 speed, int pos);
    // Sensors
    void sendReachForce(float force);
    void sendLoseForce(float force);
    void sendGetPos();

    // Receiving
    // Codes of messages, recieving from controller (sorted by importance)
    enum class Get {
        None,        // Nothing, for apply connection
        // Current state
        Waiting,     // Currently waiting for command
        Working,     // Currently moving
        // New measures
        Packet,     // One frame with new [position], [force] and [temperature]
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

    void parseMessage(const char* data, unsigned length);
};

// Object store state of device and interact with him
extern Device device;
