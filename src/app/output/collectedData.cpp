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
positions(1.0, 0.0),
forces(50.0, 50.0),
temperatures(25.0, 15.0) {}

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
        // Openning file
        SDL_IOStream* fout = SDL_IOFromFile(buffer, "w");
        // Saving to file
        save(fout);
        // Closing file
        SDL_CloseIO(fout);
    }
}

void CollectedData::addFrame(const void* _data) {
    // One packet of data
    struct Measure {
        // Values
        int type;
        float position;
        float force;
        Uint16 temperature;
    };
    const Measure* object = (Measure*)_data;
    float pos = object->position;
    float force = object->force;
    float temp = object->temperature / 10.0;

    positions.add(pos);
    forces.add(force);
    temperatures.add(temp);
    // Set that changed
    saved = true;
}

bool CollectedData::isUpdated() const {
    return saved;
}

unsigned CollectedData::getLineCount() const {
    return positions.size();
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

void CollectedData::save(SDL_IOStream* _stream) {
    // Writing data
    for (int i=0; i < positions.size(); ++i) {
        // Writing data
        SDL_IOprintf(_stream, "%f; %f; %f\n", positions[i], forces[i], temperatures[i]);
    }
    // Updating flag
    saved = false;
}
