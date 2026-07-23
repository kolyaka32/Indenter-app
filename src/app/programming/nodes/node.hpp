/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../../GUI/interface.hpp"


// posible variants of nodes
enum class NodeType {
    // System nodes (can't create)
    None,   // 'n'
    Start,  // First node, from which program started, 'i'

    // Control commands
    SetStop,    // Command to stop move, 's'
    SetMove,    // Set infinite movement in [selected] direction with [selected] speed, 'm'
    SetSteps,   // Set realtive movement in [mm], work speed, 'e'
    SetTarget,  // Set absolute [target], move to, 't'

    // Sensors, waiting until condition
    SavePos,         // Command to get and save current position, 'p'
    WaitReachForce,  // Wait until exceed force, 'r'
    WaitLoseForce,   // Wait until get less force, 'd'

    // Control commands
    Stop,        // Stop program execution, set motor to stop 'h'
    WhileStart,  // Infinite loop, store nothing, 'w'
    WhileEnd,    // Store position of loop start, 'W'
    LoopStart,   // Basic for-loop, store current position and end (as input parameter) 'l'
    LoopEnd,     // Store position of loop start, 'L'

    // Final count
    Count,
};

// Simple individual block of command to execute in language with in visual
class Node : public GUI::TextureTemplate {
private:
    // Graphical part
    SDL_FRect arrowRect;
    SDL_Texture* arrowTexture;
    const float connectDistance = 500.0;
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

    // Draw part
    void blit() const override;
    void blitCurrent() const;

    // Programming part
    // Check, if could delete current node
    bool isDeletable() const;
    // Try connect upper pin of current node to target
    bool connectUpTo(Node* target);
    // Try connect bottom pin of current node to target
    bool connectBottomTo(Node* target);
    // Create useful copy of current node
    virtual Node* copy();
    // Return connection pins positions
    virtual SDL_FPoint getBottomPin() const;
    virtual SDL_FPoint getUpperPin() const;
    // Move current node with all it content
    void move(float X, float Y) override;
    // Check if use this node (for it deletion)
    virtual void disconnect(const Node* node);
    // Interaction
    // Check on stop interaction with object
    virtual void checkOff(const Mouse mouse);
    // Try make action in current node (Button1) or start moving it (Some)
    virtual GUI::Code click(const Mouse mouse);
    virtual void unclick();
    virtual void type(SDL_Keycode code);
    virtual void writeString(const char* str);
    // Basic update function
    virtual void update(float mouseX);

    // Execution
    // Reset node state at start
    virtual void reset();
    // Activate current node, return nullptr, for stop or next node
    virtual Node* use();
    // Return nullptr, for stop; next node, if correct (including itself)
    virtual Node* handleGetPos(int pos);
    virtual Node* handlReachPos() const;
    virtual Node* handleReachForce() const;
    // Save node with it properties
    virtual void save(SDL_IOStream* ofstream);
};
