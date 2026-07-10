/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Object to select new component
class NodeSelector : GUI::Template {
private:
    // Array with selectable variants
    std::array<Node, unsigned(NodeType::Count)> nodes;
    
    GUI::RectBackplate background;

public:
    NodeSelector(const Window& window, float X, float Y, float W, float H);

    // Interaction
    Node* click(const Mouse mouse);  // return new node or nullptr, if don't
    bool unclick(const Mouse mouse);  // Return true, if end selection here (for deletion)
    void update();
    void blit() const override;
};
