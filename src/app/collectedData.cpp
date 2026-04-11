/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"
#include "../data/macroses.hpp"


CollectedData::CollectedData()
: saved(false) {
    // Reserving partly space for frames
    forces.reserve(200);
    temperatures.reserve(200);
}

CollectedData::~CollectedData() {
    // Check, if not saved
    if (!saved) {
        char buffer[100];
        int number = 1;
        // Finding allowable file name
        do {
            // Create new name
            SDL_snprintf(buffer, sizeof(buffer), "data-%d.csv", number);
            // Checking, file didn't exist
        } while (INVALID_FILE_ATTRIBUTES != GetFileAttributes(buffer) && GetLastError() == ERROR_FILE_NOT_FOUND);
        // Saving to file
        save(buffer);
    }
}

void CollectedData::update() {
    if (const void* data = serial.readData()) {
        // Getted new frame
        for (int i=0; i < PACKET_FORCE_LENGTH; ++i) {
            forces.emplace_back(*(Force*)data);
            data += sizeof(Force);
        }
        temperatures.emplace_back(*(Temperature*)data);
        saved = false;
    }
}

void CollectedData::blit(const Window& _window) const {
    _window.setDrawColor(BLACK);
    for (int i=0; i < forces.size(); ++i) {
        _window.drawPoint(i, forces[i]*10.0f + 100.0);
    }
    _window.setDrawColor(BLUE);
    for (int i=0; i < temperatures.size(); ++i) {
        _window.drawPoint(i, temperatures[i]+200.0);
    }
}

bool CollectedData::isSaved() {
    return saved;
}

void CollectedData::save(const char* _name) {
    // Creating output data
    std::ofstream out{_name, std::ios_base::trunc};
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
    // Closing file
    out.close();
    // Updating flag
    saved = true;
}

bool CollectedData::trySaveNew(const char* _name) {
    // Creating file name
    char buffer[100];
    SDL_snprintf(buffer, sizeof(buffer), "%s.csv", _name);
    // Check, if already exist
    if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(buffer)) {
        return false;
    }
    // Save
    save(buffer);
    return true;
}

void CollectedData::saveAnyway(const char* _name) {
    // Creating file name
    char buffer[100];
    SDL_snprintf(buffer, sizeof(buffer), "%s.csv", _name);
    // Save anyway
    save(buffer);
}
