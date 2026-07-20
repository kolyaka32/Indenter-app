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
    // Graphical part
    SDL_FRect arrowRect;
    SDL_Texture* arrowTexture;
    const float connectDistance = 100.0;
    const bool connectableUp, connectableDown;
    const bool delitable;

protected:
    // Create double-linked list
    Node* previousNode;
    Node* nextNode;
    //
    void disconnectPrevious();
    void disconnectNext();

public:
    Node(const Window& window, float X, float Y, Textures texture,
        bool connectableUp = true, bool connectableDown = true, bool delitable = true);

    // Get next connected node
    Node* getNext() const;
    // Check, if could delete current node
    bool isDeletable() const;

    // Try connect upper pin of current node to target
    bool connectUpTo(Node* target);
    // Try connect bottom pin of current node to target
    bool connectBottomTo(Node* target);
    // Draw part
    void blit() const override;
    void blitCurrent() const;

    // Virtual function, modifiable for child nodes
    // Try make action in current node (Button1) or start moving it (Some)
    virtual GUI::Code click(const Mouse mouse);
    // Basic update function
    virtual void update();
    // Create useful copy of current node
    virtual Node* copy() const;
    // Return connection pins positions
    virtual SDL_FPoint getBottomPin() const;
    virtual SDL_FPoint getUpperPin() const;
    // Move current node with all it content
    virtual void move(float X, float Y);
    // Check if use this node (for it deletion)
    virtual void disconnect(const Node* node);

    // Activate current node, return nullptr, for stop or next node
    virtual Node* use();

    // Proceed actions from get new packets
    // Return nullptr, for stop; next node, if correct (including itself)
    virtual Node* handleGetPos();
    virtual Node* handlReachPos() const;
    virtual Node* handleReachForce() const;
};
