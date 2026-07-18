/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "node.hpp"


// Node, from what program start execution
class SavePos : public Node {
private:
    /* data */

public:
    SavePos(const Window& window, float X, float Y);
    ~SavePos();
};
