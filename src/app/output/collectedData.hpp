/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "boundedArray.cpp"


// Data type
typedef float Position;
typedef float Force;
typedef float Temperature;

// Class for storing collected data and show it
class CollectedData {
 public:
    // One packet of data
    struct Measure {
        // Values
        Position position;
        Force force;
        Temperature temperature;
    };

 private:
    BoundedArray<Position> positions;
    BoundedArray<Force> forces;
    BoundedArray<Temperature> temperatures;

 protected:
    bool saved;  // Flag, is updated since last save

 public:
    CollectedData();
    ~CollectedData();
    void reset();
    void addFrame(const void* data);

    const BoundedArray<Position>& getPositions() const;
    const BoundedArray<Force>& getForces() const;
    const BoundedArray<Temperature>& getTemperatures() const;

    // Interacting with files
    bool isUpdated() const;  // Return true, if updated since last save
    unsigned getLineCount() const;  // Return current number of lines
    void save(SDL_IOStream* stream);  // Save data to selected stream
};

// Main data-storing object
extern CollectedData collectedData;
