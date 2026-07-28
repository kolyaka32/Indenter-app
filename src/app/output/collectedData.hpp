/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "boundedArray.cpp"


// Class for storing collected data and show it
class CollectedData {
 private:
    BoundedArray<float> positions;
    BoundedArray<float> forces;
    BoundedArray<float> temperatures;

 protected:
    bool saved;  // Flag, is updated since last save

 public:
    CollectedData();
    ~CollectedData();
    void reset();
    void addFrame(float position, float force, Uint16 temp);

    const BoundedArray<float>& getPositions() const;
    const BoundedArray<float>& getForces() const;
    const BoundedArray<float>& getTemperatures() const;

    // Interacting with files
    bool isUpdated() const;  // Return true, if updated since last save
    unsigned getLineCount() const;  // Return current number of lines
    float getLastForce() const;
    float getLastTemp() const;
    void save(SDL_IOStream* stream);  // Save data to selected stream
};

// Main data-storing object
extern CollectedData collectedData;
