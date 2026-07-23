/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../../GUI/interface.hpp"


// Special node for use as additional argument in function
class SubNode : public GUI::TextureTemplate {
private:
    const float connectDistance = 500.0;

protected:
    // Number of node, for correct global save/load
    // + for source, - for target
    int number;

public:
    // Movable node for connection
    SubNode(const Window& window, float X, float Y, int number, Textures texture = Textures::SubBlock);
    // Connection pin constructor
    SubNode(const Window& window, float X, float Y, Textures texture = Textures::SubBlock);

    // Interaction
    void connectSubNode(SubNode* subNode);
    bool tryConnectSubNode(SubNode* subNode);
    virtual SubNode* copy();
    int getNumber() const;
};
