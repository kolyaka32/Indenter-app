/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "boundedArray.hpp"


template <typename T>
BoundedArray<T>::BoundedArray()
: minVal(0),
maxVal(0) {
    // Reserving space for frames
    values.reserve(1000);
}

template <typename T>
BoundedArray<T>::~BoundedArray() {
    reset();
}

template <typename T>
void BoundedArray<T>::reset() {
    values.clear();
    minVal = 0;
    maxVal = 0;
}

template <typename T>
void BoundedArray<T>::add(const T _object) {
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

template <typename T>
const T BoundedArray<T>::operator[](unsigned _pos) const {
    return values[_pos];
}

template <typename T>
T BoundedArray<T>::min() const {
    return minVal;
}

template <typename T>
T BoundedArray<T>::max() const {
    return maxVal;
}

template <typename T>
unsigned BoundedArray<T>::size() const {
    return values.size();
}
