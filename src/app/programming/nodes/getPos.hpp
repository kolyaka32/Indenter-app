/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for get and save current [position]
class GetPosNode : public Node {
private:
    /* data */

public:
    GetPosNode(const Window& window, float X, float Y);
};
