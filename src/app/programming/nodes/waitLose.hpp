/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "getPos.hpp"


// Node for wait, until force decrease less then target
class WaitLoseNode : public Node {
private:
    // Data

public:
    WaitLoseNode(const Window& window, float X, float Y);
    ~WaitLoseNode();
};
