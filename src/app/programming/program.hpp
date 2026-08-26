/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "nodes/start.hpp"
#include "nodes/setStop.hpp"
#include "nodes/setMove.hpp"
#include "nodes/setStep.hpp"
#include "nodes/setTarget.hpp"
#include "nodes/getPos.hpp"
#include "nodes/waitReach.hpp"
#include "nodes/waitLose.hpp"
#include "nodes/halt.hpp"
// ! more


// Object for represent executable program
class Program {
private:
    std::vector<Node*> nodes;  // List with all nodes for draw/interaction/execution
    Node* currentNode;   // Current executing node
    Node* previousNode;  // Node, that was current in previous cycle

protected:
    int getInt(char* &c) const;
    char getChar(char* &c) const;
    char* getString(char* &c) const;
    //void skip(char* &c) const;

public:
    Program();
    void save(const char* fileName) const;
    void load(const Window& window, const char* fileName);

    // Reet prgram to empty
    void reset(const Window& window);
    // Start program execution
    void start();
    // Stop program execution
    void stop();
    // Return, if currently run any programs
    bool isExecuting();
    // Check, if program stopped
    bool isStopped();

    // Proceed action from get messages
    void handlePos(int pos);
    void handleReachPos();
    void handleReachForce();

    // Add new node
    void add(Node* node);
    // Delete node with all it connections
    void deleteNode(Node* node);
    // Get position of current node
    unsigned getNodePos(const Node* node) const;

    void checkOff(const Mouse mouse);
    GUI::Code click(const Mouse mouse, Node** node);
    void unclick();
    bool tryConnectTop(Node* node);
    bool tryConnectBottom(Node* node);
    bool tryConnectSubNode(SubNode* subNode);
    void type(SDL_Keycode code);
    void writeString(const char* str);
    void update(const Mouse mouse);
    void blit() const;
};
