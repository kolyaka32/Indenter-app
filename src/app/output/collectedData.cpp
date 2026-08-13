/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"


// Main data-storing object
CollectedData collectedData{};

CollectedData::CollectedData()
: saved(false),
positions(),
forces(),
temperatures() {}

void CollectedData::reset() {
    saved = false;
    positions.reset();
    forces.reset();
    temperatures.reset();
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
            SDL_snprintf(buffer, sizeof(buffer), "records\\data-%d.csv", number);
            // Increasing number
            number++;

            // Checking, file already exist
        } while (SDL_GetPathInfo(buffer, &info));
        // Saving to file
        save(buffer);
    }
}

void CollectedData::addFrame(float _position, float _force, Uint16 _temp) {
    positions.add(_position);
    forces.add(_force);
    temperatures.add(_temp/10.0);
    // Set that changed
    saved = true;
}

bool CollectedData::isUpdated() const {
    return saved;
}

unsigned CollectedData::getLineCount() const {
    return positions.size();
}

float CollectedData::getLastForce() const {
    if (positions.size()) {
        return forces[forces.size()-1];
    }
    return 0.0;
}

float CollectedData::getLastTemp() const {
    if (positions.size()) {
        return temperatures[temperatures.size()-1];
    }
    return 0.0;
}

const BoundedArray<float>& CollectedData::getPositions() const {
    return positions;
}

const BoundedArray<float>& CollectedData::getForces() const {
    return forces;
}

const BoundedArray<float>& CollectedData::getTemperatures() const {
    return temperatures;
}

void CollectedData::save(const char* _fileName) {
    // Getting file
    SDL_IOStream* fout = SDL_IOFromFile(_fileName, "w");
    if (fout == nullptr) {
        return;
    }

    // Writing data
    for (int i=0; i < positions.size(); ++i) {
        // Writing data
        SDL_IOprintf(fout, "%.1f; %.3f; %.1f\n", positions[i], forces[i], temperatures[i]);
    }
    // Updating flag
    saved = false;

    // Closing file
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", _fileName);
}
