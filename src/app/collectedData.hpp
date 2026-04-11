/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <vector>
#include "../data/app.hpp"
#include "../serial/serial.hpp"

// Constatnts
#define PACKET_FORCE_LENGTH 5

// Data type
typedef float Force;
typedef float Temperature;


// Class for storing collected data and show it
class CollectedData {
 private:
    std::vector<Force> forces;
    std::vector<Temperature> temperatures;

 protected:
    bool saved;  // Flag, is last save of file
    void save(const char* name);

 public:
    CollectedData();
    ~CollectedData();
    void update();
    void blit(const Window& window) const;

    // Interacting with files
    bool isSaved();  // Return true, if not saved
    bool trySaveNew(const char* name);  // Function for save at runtime to new file
};
