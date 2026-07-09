/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"
#include "../data/macroses.hpp"


// Main data-storing object
CollectedData collectedData{};

CollectedData::CollectedData()
: saved(true) {
    // Reserving partly space for frames
    forces.reserve(200);
    temperatures.reserve(200);
}

CollectedData::~CollectedData() {
    // Check, if not saved
    if (saved) {
        char buffer[100];
        int number = 1;
        SDL_PathInfo info;

        // Finding allowable file name
        do {
            // Create new name
            SDL_snprintf(buffer, sizeof(buffer), "data-%d.csv", number);
            // Increasing number
            number++;

            // Checking, file already exist
        } while (SDL_GetPathInfo(buffer, &info));
        // Saving to file
        save(buffer);
    }
}

void CollectedData::addFrame(const char* _data) {
    // Getted new frame
    for (int i=0; i < PACKET_FORCE_LENGTH; ++i) {
        forces.emplace_back(*(Force*)_data);
        _data += sizeof(Force);
    }
    temperatures.emplace_back(*(Temperature*)_data);
    saved = true;
}

bool CollectedData::isUpdated() const {
    return saved;
}

const std::vector<Force>& CollectedData::getForces() {
    return forces;
}

const std::vector<Temperature>& CollectedData::getTemperatures() {
    return temperatures;
}

void CollectedData::save(const char* _name) {
    // Creating output data
    std::ofstream out{_name, std::ios_base::trunc};
    // Writing data
    for (int i=0; i < temperatures.size(); ++i) {
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
    saved = false;
}

bool CollectedData::trySaveNew(const char* _name) {
    // Creating file name
    char buffer[100];
    SDL_snprintf(buffer, sizeof(buffer), "%s.csv", _name);
    // Check, if already exist
    SDL_PathInfo info;
    if (SDL_GetPathInfo(buffer, &info)) {
        return true;
    }
    // Save
    save(buffer);
    return false;
}

void CollectedData::saveAnyway(const char* _name) {
    // Creating file name
    char buffer[100];
    SDL_snprintf(buffer, sizeof(buffer), "%s.csv", _name);
    // Save anyway
    save(buffer);
}
