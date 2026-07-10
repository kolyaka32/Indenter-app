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
    std::array<Node*, unsigned(NodeType::Count)-3> nodes;

    GUI::RectBackplate background;

public:
    NodeSelector(const Window& window, float X, float Y, float W, float H);
    ~NodeSelector();
    template <typename Obj>
    void addNode(const Window& window, float X, float Y, float H);

    // Interaction
    Node* click(const Mouse mouse);  // return new node or nullptr, if don't
    bool unclick(const Mouse mouse);  // Return true, if end selection here (for deletion)
    void update();
    void blit() const override;
};


template <typename Obj>
void NodeSelector::addNode(const Window& _window, float _X, float _Y, float _H) {
    static unsigned count = 0;
    unsigned pos = count - nodes.size()/2;
    nodes[count] = new Obj{_window, _X, _Y+_H*pos, Textures::MenuButton};
    count++;
}
