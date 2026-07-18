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
    std::array<Node*, 7> nodes;  // ! For now without loops

    // Graphical part
    GUI::RectBackplate background;

    template <typename Obj>
    void addNode(float X, float Y, float H);

public:
    NodeSelector(const Window& window, float X, float Y, float W, float H);
    ~NodeSelector();

    // Interaction
    Node* click(const Mouse mouse);  // return new node or nullptr, if don't
    bool unclick(const Mouse mouse);  // Return true, if end selection here (for deletion)
    void update();
    void blit() const override;
};


template <typename Obj>
void NodeSelector::addNode(float _X, float _Y, float _H) {
    static int count = 0;
    float pos = _H * (count - (int)nodes.size()/2) / nodes.size();
    nodes[count] = new Obj{window, _X * window.getWidth(), (_Y + pos) * window.getHeight(), Textures::BlockStart};
    count++;
}
