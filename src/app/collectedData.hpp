/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <vector>
#include "../serial/serial.hpp"
#include "frame.hpp"


// Class for storing collected data and show it
class CollectedData : public GUI::Template {
 private:
    std::vector<ForceFrame> forceFrames;
    std::vector<TemperatureFrame> temperatureFrames;

 public:
    CollectedData(const Window& window);
    ~CollectedData();
    void update();
    void blit() const override;

    // Interacting with files
    void save(const char* name);
};
