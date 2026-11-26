/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "boundedArray.hpp"


// Class for storing collected data and show it
class CollectedData {
private:
    BoundedArray time;
    BoundedArray positions;
    BoundedArray forces;
    BoundedArray temperatures;
    float prevPos;
    float posNull;  // ! Should be moved to bounded array
    float forceNull;

protected:
    bool changed;  // Flag, is changed since last save

    void addData(Uint32 time, float position, float force, Uint16 temp);

public:
    CollectedData();
    ~CollectedData();
    void reset();
    void addFrame(Uint32 time, float position, float force, Uint16 temp);

    const BoundedArray& getPositions() const;
    const BoundedArray& getForces() const;
    const BoundedArray& getTemperatures() const;

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
