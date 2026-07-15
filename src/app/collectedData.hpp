/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "../data/app.hpp"

// Constatnts
#define PACKET_FORCE_LENGTH 5

// Data type
struct Measure {
   typedef float Force;
   typedef float Temperature;
   // Values
   int position;
   Force force;
   Temperature temp;
};



// Class for storing collected data and show it
class CollectedData {
 private:
    std::vector<Measure> measures;

 protected:
    bool saved;  // Flag, is updated since last save

 public:
    CollectedData();
    ~CollectedData();
    void reset();
    void addFrame(const Uint8* data);

    //const std::vector<Force>& getForces();
    //const std::vector<Temperature>& getTemperatures();

    // Interacting with files
    bool isUpdated() const;  // Return true, if updated since last save
    unsigned getLineCount() const;  // Return current number of lines
    void save(SDL_IOStream* stream);  // Save data to selected stream
};

// Main data-storing object
extern CollectedData collectedData;
