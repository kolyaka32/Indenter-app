/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "program.hpp"


// Object to select new component
class NodeSelector : GUI::Template {
private:
    // Array with selectable variants
    std::array<Node*, 8> nodes;  // ! For now without loops
    int count = 0;

    // Graphical part
    GUI::RectBackplate background;

    template <typename Obj>
    void addNode(float X, float Y, float H);

public:
    NodeSelector(const Window& window, float X, float Y, float W, float H) noexcept;
    ~NodeSelector() noexcept;

    // Interaction
    bool in(const Mouse mouse) const;
    void checkOff(const Mouse mouse);
    Node* click(const Mouse mouse);  // return new node or nullptr, if don't
    void unclick();
    void type(SDL_Keycode code);
    void writeString(const char* str);
    void update(const Mouse mouse);
    void blit() const override;
};


template <typename Obj>
void NodeSelector::addNode(float _X, float _Y, float _H) {
    float pos = _H * (count - (float)nodes.size()/2 + 0.5) / nodes.size();
    nodes[count] = new Obj{window, _X, _Y + pos};
    count++;
}
