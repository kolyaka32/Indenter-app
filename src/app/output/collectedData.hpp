/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "boundedArray.hpp"


// Class for storing collected data and show it
class CollectedData {
public:
    BoundedArray time;
    BoundedArray positions;
    BoundedArray forces;
    BoundedArray temperatures;

protected:
    float prevPos;  // Last get position for better saving
    bool changed;   // Flag, is changed since last save

    void addData(Uint32 time, float position, float force, Uint16 temp);

public:
    CollectedData();
    ~CollectedData();
    void reset();
    void addFrame(Uint32 time, float position, float force, Uint16 temp);

    unsigned getLineCount() const;

    void setPosNullAsLast();
    void setForceNullAsLast();
    void setForceNullAsAvar();

    bool isChanged() const;  // Return true, if changed since last save
    void trySave(const char* name);
    void save(const char* name);

    bool saveRepeat;  // Flag, is should save repeated data
};

// Main collected data-storing object
extern CollectedData collectedData;
