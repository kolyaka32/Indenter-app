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
: saved(false) {
    // Reserving partly space for frames
    measures.reserve(200);
}

void CollectedData::reset() {
    saved = false;
    measures.clear();
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

void CollectedData::addFrame(const Uint8* _data) {
    // Getted new frame
    measures.emplace_back(*(Measure*)_data);
    saved = true;
}

bool CollectedData::isUpdated() const {
    return saved;
}

unsigned CollectedData::getLineCount() const {
    return measures.size();
}

/*const std::vector<Force>& CollectedData::getForces() {
    return forces;
}

const std::vector<Temperature>& CollectedData::getTemperatures() {
    return temperatures;
}*/

void CollectedData::save(SDL_IOStream* _stream) {
    // Writing data
    for (int i=0; i < measures.size(); ++i) {
        // Writing data
        SDL_IOprintf(_stream, "%d; %f; %d\n", measures[i].position, measures[i].force, measures[i].temp);
    }
    // Updating flag
    saved = false;
}
