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
    _object += offset;
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
    offset += _offset;
}

float BoundedArray::getOffset() const {
    return offset;
}

float BoundedArray::operator[](unsigned _pos) const {
    return values[_pos];
}

unsigned BoundedArray::size() const {
    return values.size();
}

float BoundedArray::min() const {
    return minVal;
}

float BoundedArray::max() const {
    return maxVal;
}

float BoundedArray::last() const {
    if (values.size()) {
        return values[values.size() - 1];
    }
    return 0.0;
}

float BoundedArray::avr() const {
    float sum = 0.0;
    for (unsigned i=0; i < values.size(); ++i) {
        sum += values[i];
    }
    if (values.size()) {
        return sum / values.size();
    }
    return 0.0;
}
