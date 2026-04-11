/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <vector>
#include "../GUI/interface.hpp"
#include "../serial/serial.hpp"

// Constatnts
#define PACKET_FORCE_LENGTH 5

// Data type
typedef float Force;
typedef float Temperature;


// Class for storing collected data and show it
class CollectedData : public GUI::Template {
 private:
    std::vector<Force> forces;
    std::vector<Temperature> temperatures;

 public:
    CollectedData(const Window& window);
    void update();
    void blit() const override;

    // Interacting with files
    void save(const char* name);
};
