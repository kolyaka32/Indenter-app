/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../../GUI/interface.hpp"
#include "../subNodes/subNode.hpp"


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
    // Flags
    const bool connectableUp, connectableDown;
    const bool delitable;

    // Graphical part
    SDL_FRect arrowRect;
    SDL_Texture* arrowTexture;
    const float connectDistance = 500.0;

protected:
    // Create double-linked list
    Node* previousNode;
    Node* nextNode;
    //
    void disconnectPrevious();
    void disconnectNext();
    // Return connection pins positions
    SDL_FPoint getBottomPin() const;
    SDL_FPoint getUpperPin() const;

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
    // Connect current node to target
    void connectTopTo(Node* target);
    void connectBottomTo(Node* target);
    // Connect subNode to this
    virtual void connectSubNode(SubNode* target);
    // Try connect pin of current node to target pin
    bool tryConnectTopTo(Node* target);
    bool tryConnectBottomTo(Node* target);
    // Try to connect subNode to this, return true if can
    virtual bool tryConnectSubNode(SubNode* target);
    // Create useful copy of current node
    virtual Node* copy();
    // Move current node with all it content
    void move(float X, float Y) override;
    // Check if use this node (for it deletion)
    virtual void disconnect(const Node* node);
    // Get subNode to hold and place
    virtual SubNode* takeSubNode();
    // Get ID of node (for comparison in load (mostly for getPos))
    virtual int getID() const;

    // Interaction
    virtual void checkOff(const Mouse mouse);  // Check on stop interaction with object
    // Try make action in current node (Button1), Activate for take subnode or start moving it (Some)
    virtual GUI::Code click(const Mouse mouse);
    virtual void unclick();
    virtual void type(SDL_Keycode code);
    virtual void writeString(const char* str);
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
