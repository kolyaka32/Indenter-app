/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "../../data/app.hpp"


// Data type, storing getted value with known upper and lower borders
class BoundedArray {
private:
    std::vector<float> values;
    float minVal, maxVal;

public:
    BoundedArray();
    ~BoundedArray();
    // Clear all values
    void reset();
    // Add new value with update of min/max
    void add(float object);
    // Offset all values by offset (including min/max)
    void offsetBy(float offset);

    // Getters
    float operator[](unsigned pos) const;
    float min() const;
    float max() const;
    unsigned size() const;
};
