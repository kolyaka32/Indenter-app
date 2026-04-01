/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"


CollectedData::CollectedData(const Window& _window)
: Template(_window) {

}

CollectedData::~CollectedData() {}

void CollectedData::update() {
    if (const char* data = serial.readData()) {
        // Writing to RAM
    }
}

void CollectedData::blit() const {
    // !
}

void CollectedData::save(const char* _name) {
    // Creating output data
    std::ofstream out{_name};
    // Writing data
    // !
}
