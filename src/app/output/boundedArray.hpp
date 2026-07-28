/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "../../data/app.hpp"


// Data type, storing getted value with known upper and lower borders
template <typename T>
class BoundedArray {
private:
    std::vector<T> values;
    T minVal, maxVal;

public:
   BoundedArray();
   ~BoundedArray();
   void reset();
   void add(const T object);

   // Getters
   const T operator[](unsigned pos) const;
    T min() const;
    T max() const;
    unsigned size() const;
};
