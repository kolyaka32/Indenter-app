/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../../GUI/interface.hpp"


// posible variants of nodes
enum class NodeType {
    // System nodes (can't create)
    None,
    Start,  // First node, from which program started

    // Control commands
    SetStop,       // Command to stop move
    SetMove,       // Set infinite movement in [selected] direction with [selected] speed
    SetSteps,      // Set realtive movement in [mm], work speed
    SetTarget,     // Set absolute [target], move to

    // Sensors, waiting until condition
    SavePos,         // Command to get and save current position
    WaitReachForce,  // Wait until exceed force
    WaitLoseForce,   // Wait until get less force

    // Control commands
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
    // Create double-linked list
    Node* previousNode;
    Node* nextNode;
    // Graphical part
    SDL_FRect arrowRect;
    SDL_Texture* arrowTexture;

public:
    // Place at specified
    Node(const Window& window, float X, float Y, Textures texture);
    bool click(const Mouse mouse);
    void update();
    // Move current node with all it content
    void moveNode(float X, float Y);
    // Get next connected node
    Node* getNext() const;
    // Connect node to current
    bool connectTo(Node* node);
    // Check on taking current node by cursor
    Node* take(const Mouse mouse);
    // Draw part
    void blit() const override;
    void blitCurrent() const;

    // Activate current node
    // Return nullptr, for stop; next node, if correct (including itself)
    virtual Node* use();
    // Create useful copy of current node
    virtual Node* copy() const;
    // Check if use this node (for it deletion)
    virtual void disconnect(const Node* node);
    // Check, if can delete current node
    virtual bool isDeletable() const;

    // Proceed actions from get new packets
    // Return nullptr, for stop; next node, if correct (including itself)
    virtual Node* handleGetPos();
    virtual Node* handlReachPos() const;
    virtual Node* handleReachForce() const;
};
