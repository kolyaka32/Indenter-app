/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../../GUI/interface.hpp"


class Node;

// Special node for use as additional argument in function
class SubNode : public GUI::TextureTemplate {
private:
    const float connectDistance = 500.0;

protected:
    // Source node for source, nullptr for target
    Node* srcNode;

public:
    // Movable node for connection
    SubNode(const Window& window, float X, float Y, Node* srcNode, Textures texture = Textures::SubBlock);
    // Connection pin constructor
    SubNode(const Window& window, float X, float Y, Textures texture = Textures::SubBlock);

    // Interaction
    bool isNear(const SubNode* other) const;
    void moveTo(const SubNode* target);
    virtual SubNode* copy();
    Node* getSource() const;
};
