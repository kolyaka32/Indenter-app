/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "boundedArray.cpp"


// Class for storing collected data and show it
class CollectedData {
private:
    // ! Should add time scale
    BoundedArray<float> positions;  // ! Should remove templated part
    BoundedArray<float> forces;
    BoundedArray<float> temperatures;
    float prevPos;
    float posNull;  // ! Should be moved to bounded array
    float forceNull;

protected:
    bool changed;  // Flag, is changed since last save

    void addData(float position, float force, Uint16 temp);

public:
    CollectedData();
    ~CollectedData();
    void reset();
    void addFrame(float position, float force, Uint16 temp);

    const BoundedArray<float>& getPositions() const;
    const BoundedArray<float>& getForces() const;
    const BoundedArray<float>& getTemperatures() const;

    unsigned getLineCount() const;
    float getLastForce() const;
    float getLastTemp() const;

    // Offset of forces/positions
    float getPosNull() const;
    void setPosNull(float val);
    void setPosNull();
    float getForceNull() const;
    void setForceNull(float forceNull);
    void setForceNullAsLast();
    void setForceNullAsAvar();

    bool isChanged() const;  // Return true, if changed since last save
    void trySave(const char* name);
    void save(const char* name);

    bool saveRepeat;  // Flag, is should save repeated data
};

// Main collected data-storing object
extern CollectedData collectedData;
