/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <mutex>
#include "programMenu.hpp"
#include "../device.hpp"
#include "../../data/cycleTemplate.hpp"


std::vector<Node*> ProgramMenu::nodes{};
Node* ProgramMenu::currentNode{};
Node* ProgramMenu::previousNode{};

ProgramMenu::ProgramMenu(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
background(_window, _X, _Y, _W, _H, 20.0, 2.0, DARK_GREY),
title(_window, _X, _Y-_H*0.45, {"Programming", "Программирование"}, 2, Height::Info),
separateRect{(_X-_W/2)*_window.getWidth(), (_Y-_H*0.4f)*_window.getHeight(), _W*_window.getWidth(), 2},
startButton(_window, _X+_W*0.37, _Y-_H*0.45, 0.03, Textures::ResumePauseButton),
haltButton(_window,  _X+_W*0.45, _Y-_H*0.45, 0.03, Textures::HaltButton),
saveButton(_window,  _X-_W*0.45, _Y-_H*0.45, 0.03, Textures::SaveButton),
loadButton(_window,  _X-_W*0.37, _Y-_H*0.45, 0.03, Textures::LoadButton),
stoppedInfo(_window, _X+_W*0.16, _Y-_H*0.38, {"Program stopped", "Программа остановлена"}, 1000),
netConnectedInfo(_window, _X+_W*0.16, _Y-_H*0.38, {"Not connected", "Не подключён"}, 1000),
selector(_window, _X-_W/3, _Y+_H*0.05, _W/3, _H*0.9),
filterText{"Program file", "Файл программы"},
filter{filterText.getString().c_str(), "prg"} {
    // Getting location
    char* directory = SDL_GetCurrentDirectory();
    SDL_CreateDirectory("scripts");
    snprintf(saveLocation, sizeof(saveLocation), "%sscripts\\script.prg", directory);
    SDL_free(directory);
    currentNode = nullptr;
    holdingNode = nullptr;
    // On first entarance
    if (!CycleTemplate::isRestarted()) {
        reset();
    }
}

void ProgramMenu::reset() {
    nodes.clear();
    // Add first node
    nodes.emplace_back(new StartNode{window, 0.5, 0.5});
}

void ProgramMenu::deleteNode(Node* _node) {
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

void ProgramMenu::start() {
    // Resetting all nodes
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->reset();
    }
    // Always start from first node (start, can't be changed)
    currentNode = nodes[0];
    logger.additional("Start program execution");
}

bool ProgramMenu::click(const Mouse _mouse) {
    // Check on stop interaction
    selector.checkOff(_mouse);
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->checkOff(_mouse);
    }
    // Check on buttons press
    if (startButton.in(_mouse)) {
        if (device.isConnected()) {
            start();
        } else {
            netConnectedInfo.reset();
        }
        return true;
    }
    if (haltButton.in(_mouse)) {
        currentNode = nullptr;
        logger.additional("Stop program execution");
        return true;
    }
    if (saveButton.in(_mouse)) {
        window.showSaveFileDialog(save, &filter, 1, saveLocation, this);
        return true;
    }
    if (loadButton.in(_mouse)) {
        window.showOpenFileDialog(load, &filter, 1, saveLocation, false, this);
        return true;
    }
    // Check, if start movement of node
    for (unsigned i=0; i < nodes.size(); ++i) {
        if (int code = nodes[i]->click(_mouse)) {
            if (code == GUI::Some) {
                holdingNode = nodes[i];
                // Save current pos
                lastPos = _mouse.getPos();
                logger.additional("Start holding %d", i);
            }
            return true;
        }
    }

    // Check, if create new node
    if (holdingNode = selector.click(_mouse)) {
        // Add to global list
        nodes.emplace_back(holdingNode);
        // Save position to move
        lastPos = _mouse.getPos();
        return true;
    }
    return false;
}

void ProgramMenu::unclick(const Mouse _mouse) {
    if (holdingNode) {
        // Check, if delete node
        if (selector.in(_mouse)) {
            deleteNode(holdingNode);
            holdingNode = nullptr;
            return;
        }

        // Try link holding node (first) to previous node
        for (int i=0; i < nodes.size(); ++i) {
            if (holdingNode->connectUpTo(nodes[i])) {
                logger.additional("Connect node up to %d", i);
                holdingNode = nullptr;
                return;
            }
        }
        // Find last holding node
        Node* lastNode = holdingNode;
        while (lastNode->getNext()) {
            lastNode = lastNode->getNext();
        }
        // Try link last node to node
        for (int i=0; i < nodes.size(); ++i) {
            if (lastNode->connectBottomTo(nodes[i])) {
                holdingNode = nullptr;
                logger.additional("Connect node bottom to %d", i);
                return;
            }
        }

        // Standart stop moving
        holdingNode = nullptr; 
        logger.additional("Stop movement");
    }
    // Check on unclicking on nodes
    selector.unclick();
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->unclick();
    }
}

void ProgramMenu::type(SDL_Keycode _code) {
    selector.type(_code);
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->type(_code);
    }
}

void ProgramMenu::writeString(const char* _str) {
    selector.writeString(_str);
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->writeString(_str);
    }
}

void ProgramMenu::update(const Mouse _mouse) {
    // Update info boxes
    netConnectedInfo.update();
    stoppedInfo.update();
    selector.update(_mouse);

    // Check for movement of node
    if (holdingNode) {
        // Get relative movement
        float dx = (_mouse.getX() - lastPos.x) / window.getWidth();
        float dy = (_mouse.getY() - lastPos.y) / window.getHeight();
        // Move this and connected nodes in reverse order
        Node* moveNode = holdingNode;
        while (moveNode) {
            moveNode->move(dx, dy);
            moveNode = moveNode->getNext();
        }
        // Update position
        lastPos = _mouse.getPos();
    }

    // Update nodes
    for (int i=0; i < nodes.size(); ++i) {
        nodes[i]->update(_mouse.getX());
    }

    if (currentNode != previousNode) {
        // Save current state as previous
        previousNode = currentNode;

        // Check, if stopped working
        if (currentNode == nullptr) {
            // Show message
            stoppedInfo.reset();
        } else {
            // Executing current node
            currentNode = currentNode->use();
            // ! Could add check for too much time for resend
        }
    }
}

void ProgramMenu::handlePos(int _pos) {
    currentNode = currentNode->handleGetPos(_pos);
}

void ProgramMenu::handleReachPos() {
    currentNode = currentNode->handlReachPos();
}

void ProgramMenu::handleReachForce() {
    currentNode = currentNode->handleReachForce();
}

bool ProgramMenu::isExecuting() {
    return currentNode != nullptr;
}

void ProgramMenu::stop() {
    currentNode = nullptr;
}

void ProgramMenu::blit() const {
    background.blit();
    title.blit();
    window.setDrawColor(BLACK);
    window.drawRect(separateRect);
    selector.blit();
    startButton.blit();
    haltButton.blit();
    saveButton.blit();
    loadButton.blit();
    netConnectedInfo.blit();
    stoppedInfo.blit();

    // Draw program in reverse order
    for (unsigned i = nodes.size(); i > 0; --i) {
        nodes[i-1]->blit();
    }
    // Draw current node highlight
    if (currentNode) {
        currentNode->blitCurrent();
    }
}

void ProgramMenu::save(SDL_IOStream* fout) const {
    // Writing main nodes linked-list to it
    Node* node = nodes[0];
    while (node) {
        // Save node
        node->save(fout);
        // Get next
        node = node->getNext();
    }
}

void ProgramMenu::load(SDL_IOStream* fin) {
    // Clearing previous
    reset();

    // Loading nodes from it
    char buffer[2000];
    SDL_ReadIO(fin, buffer, sizeof(buffer));
    Node* previousNode = nodes[0];
    // Read all getted data
    for (char *c = buffer; *c; ++c) {
        // Create node by text description
        switch (*c) {
        case 'i':
            // Start node
            // Ignore
            break;

        case 'm':
            // !
            //nodes.emplace_back(new SetMoveNode{window, previousNode, });
            break;

        // ! Finish loading all
        
        default:
            break;
        }
    }
}


static std::mutex saveMutex;

void ProgramMenu::save(void* _userdata, const char* const* _filelist, int _filter) {
    // Check, if all avaliable
    if (_filelist == nullptr || _filter < 0) {
        return;
    }
    // Getting file
    SDL_IOStream* fout = SDL_IOFromFile(*_filelist, "w");
    if (fout == nullptr) {
        return;
    }
    // Locking, while saving
    saveMutex.lock();

    ProgramMenu* menu = (ProgramMenu*)_userdata;
    menu->save(fout);

    saveMutex.unlock();
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", *_filelist);
}

void ProgramMenu::load(void* _userdata, const char* const* _filelist, int _filter) {
    // Check, if all avaliable
    if (_filelist == nullptr || _filter < 0) {
        return;
    }
    // Getting file
    SDL_IOStream* fin = SDL_IOFromFile(*_filelist, "r");
    if (fin == nullptr) {
        return;
    }
    // Locking, while saving
    saveMutex.lock();

    ProgramMenu* menu = (ProgramMenu*)_userdata;
    menu->load(fin);

    saveMutex.unlock();
    SDL_CloseIO(fin);
    logger.additional("Program loaded from %s", *_filelist);
}
