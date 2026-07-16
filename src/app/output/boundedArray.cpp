/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "boundedArray.hpp"


template <typename T>
BoundedArray<T>::BoundedArray(const T _maxVal, const T _minVal)
: maxVal(_maxVal),
minVal(_minVal) {
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
}

template <typename T>
void BoundedArray<T>::add(const T _object) {
    values.emplace_back(_object);
    // Update min and max
    if (_object < minVal) {
        minVal = _object;
    } else if (_object > maxVal) {
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
