/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node for move by setted [distance]
class SetStepNode : public Node {
private:
    /* data */

public:
    SetStepNode(const Window& window, float X, float Y);
    ~SetStepNode();
};
