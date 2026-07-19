/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node, from what program start execution
class StartNode : public Node {
private:
    /* data */

public:
    StartNode(const Window& window, float X, float Y);
};
