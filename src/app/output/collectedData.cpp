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
temperatures(),
forceNull(0.0) {}

void CollectedData::reset() {
    saved = false;
    positions.reset();
    forces.reset();
    temperatures.reset();
}

CollectedData::~CollectedData() {
    // Check, if not saved
    if (saved) {
        trySave("data");
    }
}

void CollectedData::addFrame(float _position, float _force, Uint16 _temp) {
    positions.add(_position);
    // Adding force with offset
    forces.add(_force + forceNull);
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

float CollectedData::getForceNull() const {
    return forceNull;
}

void CollectedData::setForceNull(float _forceNull) {
    if (forces.size()) {
        // ! Should check timings - O(n) complexity
        forces.offsetBy(_forceNull);
    }
    forceNull = _forceNull;
}

void CollectedData::setForceNullAsLast() {
    // Getting force null as last element
    if (forces.size()) {
        setForceNull(-forces[forces.size() - 1]);
    }
}

void CollectedData::setForceNullAsAvar() {
    // Getting force null as last element
    if (forces.size()) {
        // Finding avarage
        float sumForce = 0.0;
        for (int i=0; i < forces.size(); ++i) {
            sumForce += forces[i];
        }
        setForceNull(-sumForce/forces.size());
    }
}

void CollectedData::trySave(const char* _name) {
    // Find avaliable name
    char buffer[100];
    int number = 1;
    SDL_PathInfo info;

    do {
        // Create new name
        SDL_snprintf(buffer, sizeof(buffer), "records\\%s-%d.csv", _name, number);
        number++;

        // Check if file already exist
    } while (SDL_GetPathInfo(buffer, &info));

    // Saving to file
    save(buffer);
}

void CollectedData::save(const char* _fileName) {
    // Open file
    SDL_IOStream* fout = SDL_IOFromFile(_fileName, "w");
    if (fout == nullptr) {
        return;
    }

    // Write data
    for (int i=0; i < positions.size(); ++i) {
        SDL_IOprintf(fout, "%.1f; %.3f; %.1f\n", positions[i], forces[i], temperatures[i]);
    }
    // Updating flag
    saved = false;

    // Closing file
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", _fileName);
}
