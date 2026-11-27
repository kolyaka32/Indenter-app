/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../../GUI/interface.hpp"
#include "../subNodes/subNode.hpp"


// posible variants of nodes
enum class NodeType : char {
    // System nodes (can't create)
    None  = 'n',
    Start = 'i',  // First node, from which program started

    // Control commands
    SetStop   = 's',  // Command to stop move
    SetMove   = 'm',  // Set infinite movement in [selected] direction with [selected] speed
    SetSteps  = 'e',  // Set realtive movement in [mm], work speed
    SetTarget = 't',  // Set absolute [target], move to

    // Sensors, waiting until condition
    GetPos         = 'p',  // Command to get and save current position
    WaitReachForce = 'r',  // Wait until exceed [force]
    WaitLoseForce  = 'd',  // Wait until get less [force]
    SetForceNull   = 'u',  // Set force null [type]
    SetPosNull     = 'y',  // Set position null
    SaveData       = 'a',  // Save collected data as [name]

    // Control commands
    Comment = 'c',  // [Comment] for readability
    Halt    = 'h',  // Stop program execution, set motor to stop 
    Wait    = 'v',  // Node for wait time in [sec]
    //WhileStart = 'w',  // Infinite loop, store nothing
    //WhileEnd   = 'W',  // Store position of loop start
    //LoopStart  = 'l',  // Basic for-loop, store current position and end (as input parameter)
    //LoopEnd    = 'L',  // Store position of loop start
};

// Simple individual block of command to execute in language with in visual
class Node : public GUI::ImageButton {
private:
    // Flags
    const bool connectableUp;
    const bool connectableDown;
    const bool delitable;

    // Graphical part
    GUI::ImageButton arrow;
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
    // Save all basic parameters
    void saveMain(SDL_IOStream* ofstream, NodeType type);

    // Internal types
    typedef Uint8 Speed;  // Speeds: slow=1, normal=2, fast=3
    typedef bool Direction;  // false for down and true for up

    Speed getSpeed(char letter) const;
    char getLetter(Speed speed) const;
    void getNextSpeed(Speed& current) const;
    void blitSpeed(Speed speed, const SDL_FRect rect) const;

    Direction getDirection(char letter) const;
    char getLetter(Direction direction) const;
    void blitDirection(Direction direction, const SDL_FRect rect) const;

public:
    Node(const Window& window, float X, float Y, Textures texture,
        bool connectableUp = true, bool connectableDown = true, bool delitable = true);
    virtual ~Node() noexcept;

    // Interaction
    // Create useful copy of current node
    virtual Node* copy();
    // Move current node with all it content
    void move(float X, float Y) override;
    // Check on stop interaction with object
    virtual void checkOff(const Mouse mouse);
    // Try make action in current node (Button1), Activate for take subnode or start moving it (Some)
    virtual GUI::Code click(const Mouse mouse);
    virtual void unclick();
    virtual bool type(SDL_Keycode code);
    virtual bool writeString(const char* str);
    // Get subNode to hold and place
    virtual SubNode* takeSubNode();
    virtual void update(float mouseX);
    void blit() const override;
    void blitCurrent() const;

    // Programming part
    // Forced connect current node to target
    void connectTopTo(Node* target);
    void connectBottomTo(Node* target);
    // Forced connect subNode to this
    virtual void connectSubNode(SubNode* target);
    // Try connect pin of current node to target pin, return if could
    bool tryConnectTopTo(Node* target);
    bool tryConnectBottomTo(Node* target);
    // Try to connect subNode to this
    virtual bool tryConnectSubNode(SubNode* target);
    // Return if could delete current node
    bool isDeletable() const;
    // Check if use this node (for it deletion)
    virtual void disconnect(const Node* node);

    // Execution
    // Get next connected node
    Node* getNext() const;
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
