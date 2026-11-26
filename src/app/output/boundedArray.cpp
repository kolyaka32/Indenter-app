/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "boundedArray.hpp"


BoundedArray::BoundedArray()
: minVal(0),
maxVal(0) {
    // Reserving space for frames
    values.reserve(1000);
}

BoundedArray::~BoundedArray() {
    reset();
}

void BoundedArray::reset() {
    values.clear();
    minVal = 0;
    maxVal = 0;
}

void BoundedArray::add(float _object) {
    values.emplace_back(_object);
    // Check, if first value
    if (values.size() == 1) {
        minVal = _object;
        maxVal = _object;
        return;
    }
    // Update min and max
    if (_object < minVal) {
        minVal = _object;
    }
    if (_object > maxVal) {
        maxVal = _object;
    }
}

void BoundedArray::offsetBy(float _offset) {
    // Move all values
    for (unsigned i=0; i < values.size(); ++i) {
        values[i] += _offset;
    }
    // Move borers
    minVal += _offset;
    maxVal += _offset;
}

float BoundedArray::operator[](unsigned _pos) const {
    return values[_pos];
}

float BoundedArray::min() const {
    return minVal;
}

float BoundedArray::max() const {
    return maxVal;
}

unsigned BoundedArray::size() const {
    return values.size();
}
