/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "getPos.hpp"


// Node for absolute movement to stored 
class SetTargetNode : public Node {
private:
    // Data
    GetPosNode* positionNode;

public:
    SetTargetNode(const Window& window, float X, float Y);
    ~SetTargetNode();
};
