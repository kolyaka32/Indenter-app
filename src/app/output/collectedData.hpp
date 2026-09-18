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
    float forceNull;

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

    bool isUpdated() const;  // Return true, if updated since last save
    unsigned getLineCount() const;
    float getLastForce() const;
    float getLastTemp() const;
    float getForceNull() const;
    // Set offset of all force elements
    void setForceNull(float forceNull);
    void setForceNullAsLast();
    void setForceNullAsAvar();
    // Save
    void trySave(const char* name);
    void save(const char* name);
};

// Main collected data-storing object
extern CollectedData collectedData;
