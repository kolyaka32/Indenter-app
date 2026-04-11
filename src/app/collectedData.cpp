/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"
#include "../data/macroses.hpp"


CollectedData::CollectedData(const Window& _window)
: Template(_window) {
    // Reserving partly space for frames
    forces.reserve(200);
    temperatures.reserve(200);
}

void CollectedData::update() {
    if (const void* data = serial.readData()) {
        // Getted new frame
        for (int i=0; i < PACKET_FORCE_LENGTH; ++i) {
            forces.emplace_back(*(Force*)data);
            data += sizeof(Force);
        }
        temperatures.emplace_back(*(Temperature*)data);
    }
}

void CollectedData::blit() const {
    window.setDrawColor(BLACK);
    for (int i=0; i < forces.size(); ++i) {
        window.drawPoint(i, forces[i]*10.0f + 100.0);
    }
    window.setDrawColor(BLUE);
    for (int i=0; i < temperatures.size(); ++i) {
        window.drawPoint(i, temperatures[i]+200.0);
    }
}

void CollectedData::save(const char* _name) {
    // Creating file name
    char buffer[100];
    SDL_snprintf(buffer, sizeof(buffer), "%s.csv", _name);

    // Creating output data
    std::ofstream out{buffer};
    // Writing data
    int length = min(temperatures.size(), forces.size()/PACKET_FORCE_LENGTH);
    for (int i=0; i < length; ++i) {
        // Writing forces at this moment
        for (int j=0; j < PACKET_FORCE_LENGTH; ++j) {
            // Getting current position
            int pos = i * PACKET_FORCE_LENGTH + j;
            out << pos << ';';
            // Writing current force
            out << forces[pos] << ';';
            // Writing current temperature (once per packet)
            out << temperatures[i] << '\n';
        }
    }
    out.close();
}
