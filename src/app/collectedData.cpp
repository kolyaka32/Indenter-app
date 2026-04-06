/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"


CollectedData::CollectedData(const Window& _window)
: Template(_window) {
    // Reserving partly space for frames
    forceFrames.reserve(200);
    temperatureFrames.reserve(200);
}

CollectedData::~CollectedData() {}

void CollectedData::update() {
    if (const void* data = serial.readData()) {
        // Getted new frame
        for (int i=0; i < PACKET_FORCE_LENGTH; ++i) {
            forceFrames.emplace_back(*(Force*)data);
            data += sizeof(Force);
        }
        temperatureFrames.emplace_back(*(Temperature*)data);
    }
}

void CollectedData::blit() const {
    // !
    window.setDrawColor(BLACK);
    for (int i=0; i < forceFrames.size(); ++i) {
        forceFrames[i].blit(i, window);
    }
    window.setDrawColor(BLUE);
    for (int i=0; i < temperatureFrames.size(); ++i) {
        forceFrames[i].blit(i, window);
    }
}

void CollectedData::save(const char* _name) {
    // Creating output data
    std::ofstream out{_name};
    // Writing data
    // !
}
