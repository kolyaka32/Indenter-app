/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"
#include "../data/macroses.hpp"


// Main data-storing object
CollectedData collectedData{};

void CollectedData::reset() {
    saved = false;
    forces.clear();
    temperatures.clear();
}

CollectedData::CollectedData()
: saved(false) {
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
            SDL_snprintf(buffer, sizeof(buffer), "datas\\data-%d.csv", number);
            // Increasing number
            number++;

            // Checking, file already exist
        } while (SDL_GetPathInfo(buffer, &info));
        // Openning file
        SDL_IOStream* fout = SDL_IOFromFile(buffer, "w");
        // Saving to file
        save(fout);
        // Closing file
        SDL_CloseIO(fout);
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

void CollectedData::save(SDL_IOStream* _stream) {
    // Writing data
    for (int i=0; i < temperatures.size(); ++i) {
        // Writing forces at this moment
        for (int j=0; j < PACKET_FORCE_LENGTH; ++j) {
            // Getting current position
            int pos = i * PACKET_FORCE_LENGTH + j;
            // Writing data
            SDL_IOprintf(_stream, "%d; %f; %f\n", forces[pos], temperatures[i]);
        }
    }
    // Updating flag
    saved = false;
}
