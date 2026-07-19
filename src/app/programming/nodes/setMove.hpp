/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for set movement in selected [direction] with selected [speed]
class SetMoveNode : public Node {
private:
    /* data */

public:
    SetMoveNode(const Window& window, float X, float Y);
};
