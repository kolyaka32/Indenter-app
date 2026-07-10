/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../GUI/interface.hpp"


// posible variants of nodes
enum class NodeType {
    None,

    // Commands
    SetSpeed,      // Set specified speed (as input, in both directions)
    SetStop,       // Command to stop move

    // Sensors, waiting until condition
    WaitNone,      // Infinite wait
    WaitPosition,  // Wait until passed specified steps number
    WaitForce,     // Wait until got force

    // Control commands
    Start,         // First node, from which it started
    WhileStart,    // Infinite loop, store nothing
    WhileEnd,      // Store position of loop start
    LoopStart,     // Basic for-loop, store current position and end (as input parameter)
    LoopEnd,       // Store position of loop start

    // Final count
    Count,
};

// Simple individual block of command to execute in language with in visual
class Node : public GUI::TextureTemplate {
private:
    

public:
    // Place at specified
    Node(const Window& window, float X, float Y, Textures texture);
    bool click(const Mouse mouse);
    void update();
    void blit() const override;
};
