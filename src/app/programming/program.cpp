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

    // Writing main nodes linked-list to it
    Node* node = nodes[0];
    while (node) {
        // Save node
        node->save(fout);
        // Get next
        node = node->getNext();
    }

    // LClose file
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", _fileName);
}

void Program::load(const Window& _window, const char* _fileName) {
    // Getting file
    SDL_IOStream* fin = SDL_IOFromFile(_fileName, "r");
    if (fin == nullptr) {
        return;
    }

    // Clearing previous
    reset(_window);

    // Loading data to buffer
    char buffer[2000];
    SDL_ReadIO(fin, buffer, sizeof(buffer));

    // Struct for save nodes with corresponding subNode argument
    struct NodeLoad {
        char type;
        Node* node;
        int number;
    };
    // Array with all loaded getPosition node for connection
    std::vector<NodeLoad> positionLoad;
    // Array with all loaded setTarget node for connection
    std::vector<NodeLoad> targetLoads;
    // Argument for use in switch
    int argument = 0;
    Node* node = nullptr;
    Node* previousNode = nodes[0];
    // Read all getted data
    for (char* c = buffer; *c; ++c) {
        // Create node by text description
        switch (*c) {
        case 'i':
            // Start node
            // Ignore
            continue;

        case 's':
            nodes.emplace_back(new SetStopNode{_window, 0.0, 0.0});
            break;

        case 'm':
            nodes.emplace_back(new SetMoveNode{_window, 0.0, 0.0, *(c+1), *(c+2)});
            break;

        case 'e':
            nodes.emplace_back(new SetStepNode{_window, 0.0, 0.0, *(c+1), c+2});
            break;

        case 't':
            node = new SetTargetNode{_window, 0.0, 0.0, *(++c)};
            // Getting argument
            argument = 0;
            for (c++; (*c >= '0') && (*c <= '9'); ++c) {
                argument = argument*10 + *c - '0';
            }
            // Check, if required to connect
            if (argument) {
                // Saving node for future argument set
                targetLoads.emplace_back(NodeLoad{'t', node, argument});
            }
            nodes.emplace_back(node);
            break;

        case 'p':
            node = new GetPosNode{_window, 0.0, 0.0};
            // Getting argument
            argument = 0;
            for (c++; (*c >= '0') && (*c <= '9'); ++c) {
                argument = argument*10 + *c - '0';
            }
            // Check, if required to connect
            if (argument) {
                // Saving node for future use as argument
                positionLoad.emplace_back(NodeLoad{'p', node, argument});
            }
            nodes.emplace_back(node);
            break;

        case 'r':
            nodes.emplace_back(new WaitReachNode{_window, 0.0, 0.0, c+1});
            break;

        case 'd':
            nodes.emplace_back(new WaitLoseNode{_window, 0.0, 0.0, c+1});
            break;

        case 'h':
            nodes.emplace_back(new HaltNode{_window, 0.0, 0.0});
            break;
        // ! Finish adding all nodes

        default:
            continue;
        }
        nodes.back()->connectTopTo(previousNode);
        previousNode = nodes.back();
    }
    // SubNodes connection
    for (int load=0; load < targetLoads.size(); ++load) {
        // Find corresponding getPos
        Node* sourceNode = nullptr;
        for (int i=0; i < positionLoad.size(); ++i) {
            if (positionLoad[i].number == targetLoads[load].number) {
                sourceNode = positionLoad[i].node;
                break;
            }
        }
        // Connect node as source and this as target
        if (sourceNode) {
            SubNode* sourceSubNode = sourceNode->takeSubNode();
            if (sourceSubNode) {
                targetLoads[load].node->connectSubNode(sourceSubNode);
                continue;
            }
        }
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
