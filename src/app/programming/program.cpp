/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */
#include "program.hpp"


Program::Program() {}

void Program::save(const char* _fileName) const {
    // Getting file
    SDL_IOStream* fout = SDL_IOFromFile(_fileName, "w");
    if (fout == nullptr) {
        return;
    }

    // Writing all nodes
    for (int i=0; i < nodes.size(); ++i) {
        // Save node data
        nodes[i]->save(fout);
        // Write string end
        SDL_IOprintf(fout, "\n");
    }

    // Close file
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", _fileName);
}

int Program::getArgument(char** c) const {
    // Getting argument
    int argument = 0;
    for (; (**c >= '0') && (**c <= '9'); ++(*c)) {
        argument = argument*10 + **c - '0';
    }
    return argument;
}

void Program::skip(char** c) const {
    while (**c && (**c != '\n')) {(*c)++;}
}

void Program::load(const Window& _window, const char* _fileName) {
    // Getting file
    SDL_IOStream* fin = SDL_IOFromFile(_fileName, "r");
    if (fin == nullptr) {
        return;
    }

    // Clearing previous
    nodes.clear();
    currentNode = nullptr;
    GetPosNode::resetCounter();

    // Loading data to buffer
    char buffer[2000];
    size_t length = SDL_ReadIO(fin, buffer, sizeof(buffer));
    buffer[length] = '\0';

    // Struct for save nodes with corresponding subNode argument
    struct NodeLoad {
        char type;  // Not using, for better comparison
        Node* node;
        unsigned next;
        unsigned subNode;
    };
    // Array with all loaded nodes for connection
    std::vector<NodeLoad> connections;

    // Read all getted data
    for (char* c = buffer; *c; ++c) {
        // Get type
        char type = *c;
        c++;
        if (*c == '\0') {
            break;
        }
        // Get x position
        c++;  // Skip space
        float x = getArgument(&c) / 100.0;
        if (*c == '\0') {
            break;
        }
        // Get y position
        c++;  // Skip space
        float y = getArgument(&c) / 100.0;
        if (*c == '\0') {
            break;
        }
        // Get next
        c++;  // Skip space
        unsigned next = getArgument(&c);
        if (*c == '\0') {
            break;
        }
        // Subnode
        unsigned subNode = 0;

        // Data for switch
        Node* node = nullptr;
        // Create node by text description
        switch (type) {
        case 'i':
            node = new StartNode{_window, x, y};
            break;

        case 's':
            node = new SetStopNode{_window, x, y};
            break;

        case 'm':
            c++;
            if (c[0] == '\0' || c[1] == '\0' || c[2] == '\0') {
                break;
            }
            node = new SetMoveNode{_window, x, y, *c, *(c+2)};
            c += 3;
            break;

        case 'e':
            c++;
            if (c[0] == '\0' || c[1] == '\0' || c[2] == '\0') {
                break;
            }
            node = new SetStepNode{_window, x, y, *c, c+2};
            c += 2;
            skip(&c);
            break;

        case 't':
            c++;
            if (*c == '\0') {
                break;
            }
            node = new SetTargetNode{_window, x, y, *c};
            c++;
            if (*c == '\0') {
                break;
            }
            c++;
            subNode = getArgument(&c);
            break;

        case 'p':
            node = new GetPosNode{_window, x, y};
            break;

        case 'r':
            c++;
            node = new WaitReachNode{_window, x, y, c};
            skip(&c);
            break;

        case 'd':
            c++;
            node = new WaitLoseNode{_window, x, y, c};
            skip(&c);
            break;

        case 'h':
            node = new HaltNode{_window, x, y};
            break;
        // ! Finish adding all nodes

        default:
            continue;
        }
        if (node) {
            // Add node to main list
            nodes.emplace_back(node);
            // Add to connection list
            connections.emplace_back(NodeLoad{type, node, next, subNode});
        }
    }
    // Nodes and subnodes connection
    for (int i=0; i < connections.size(); ++i) {
        // Connect next node
        if (connections[i].next && connections[i].next <= nodes.size()) {
            nodes[connections[i].next-1]->connectTopTo(connections[i].node);
        }
        // Connect subNode
        if (connections[i].subNode && connections[i].subNode < nodes.size()) {
            // Try take node
            SubNode* sourceSubNode = nodes[connections[i].subNode-1]->takeSubNode();
            // Place it
            if (sourceSubNode) {
                connections[i].node->connectSubNode(sourceSubNode);
            }
        }
    }
    // Additional check, if enough nodes
    if (nodes.size() == 0) {
        reset(_window);
    }
    // Close file
    SDL_CloseIO(fin);
    logger.additional("Program loaded from %s", _fileName);
}

void Program::deleteNode(Node* _node) {
    // Check all connected nodes
    while (_node) {
        if (_node->isDeletable()) {
            // Update all nodes to check on connected
            int node = 0;
            for (int i=0; i < nodes.size(); ++i) {
                if (nodes[i] == _node) {
                    node = i;
                } else {
                    nodes[i]->disconnect(_node);
                }
            }
            // Move to next node
            _node = _node->getNext();
            // Remove from array
            delete nodes[node];
            nodes.erase(nodes.begin() + node);
            logger.additional("Deleted node %d", node);
        } else {
            // Move to next node
            _node = _node->getNext();
        }
    }
}

unsigned Program::getNodePos(const Node* _node) const {
    if (_node == nullptr) {
        return 0;
    }
    for (int i=0; i < nodes.size(); ++i) {
        if (nodes[i] == _node) {
            return i+1;
        }
    }
    return 0;
}

void Program::reset(const Window& _window) {
    nodes.clear();
    currentNode = nullptr;
    GetPosNode::resetCounter();
    // Add first node
    nodes.emplace_back(new StartNode{_window, 0.5, 0.3});
}

void Program::handlePos(int _pos) {
    if (currentNode) {
        currentNode = currentNode->handleGetPos(_pos);
    }
}

void Program::handleReachPos() {
    if (currentNode) {
        currentNode = currentNode->handlReachPos();
    }
}

void Program::handleReachForce() {
    if (currentNode) {
        currentNode = currentNode->handleReachForce();
    }
}

bool Program::isExecuting() {
    return currentNode != nullptr;
}

bool Program::isStopped() {
    if (currentNode != previousNode) {
        // Save current state as previous
        previousNode = currentNode;

        // Check, if stopped working
        if (currentNode == nullptr) {
            return true;
        } else {
            // Executing current node
            currentNode = currentNode->use();
        }
    }
    // ! Could add check for too much time for resend
    return false;
}

void Program::start() {
    // Resetting all nodes
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->reset();
    }
    // Always start from first node (start, can't be changed)
    currentNode = nodes[0];
}

void Program::stop() {
    if (currentNode) {
        currentNode = nullptr;
        logger.additional("Stop program execution");
    }
}

void Program::checkOff(const Mouse _mouse) {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->checkOff(_mouse);
    }
}

GUI::Code Program::click(const Mouse _mouse, Node** _node) {
    for (unsigned i=0; i < nodes.size(); ++i) {
        if (GUI::Code code = nodes[i]->click(_mouse)) {
            *_node = nodes[i];
            return code;
        }
    }
    return GUI::None;
}

void Program::add(Node* _node) {
    nodes.emplace_back(_node);
}

bool Program::tryConnectTop(Node* _node) {
    for (int i=0; i < nodes.size(); ++i) {
        if (_node->tryConnectTopTo(nodes[i])) {
            return true;
        }
    }
    return false;
}

bool Program::tryConnectBottom(Node* _node) {
    // Find last holding node
    Node* lastNode = _node;
    while (lastNode->getNext()) {
        lastNode = lastNode->getNext();
    }
    // Try link last node to node
    for (int i=0; i < nodes.size(); ++i) {
        if (lastNode->tryConnectBottomTo(nodes[i])) {
            return true;
        }
    }
    return false;
}

bool Program::tryConnectSubNode(SubNode* _subNode) {
    for (int i=0; i < nodes.size(); ++i) {
        if (nodes[i]->tryConnectSubNode(_subNode)) {
            return true;
        }
    }
    return false;
}

void Program::unclick() {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->unclick();
    }
}

void Program::type(SDL_Keycode _code) {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->type(_code);
    }
}

void Program::writeString(const char* _str) {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->writeString(_str);
    }
}

void Program::update(const Mouse _mouse) {
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->update(_mouse.getX());
    }
}

void Program::blit() const {
    // Draw program in reverse order
    for (unsigned i = nodes.size(); i > 0; --i) {
        nodes[i-1]->blit();
    }
    // Draw current node highlight
    if (currentNode) {
        currentNode->blitCurrent();
    }
}
