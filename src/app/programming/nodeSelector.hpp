/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

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
    NodeSelector(const Window& window, float X, float Y, float W, float H);
    ~NodeSelector();

    bool in(const Mouse mouse) const;

    // Interaction
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
