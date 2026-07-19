/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "getPos.hpp"


// Node for wait, until force exceed target
class WaitReachNode : public Node {
private:
    // Data

public:
    WaitReachNode(const Window& window, float X, float Y);
};
