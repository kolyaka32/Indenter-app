/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "../GUI/interface.hpp"


// Constatnts
typedef float Force;
typedef float Temperature;
#define PACKET_FORCE_LENGTH 5


// Object for storing one frame getted dat
class ForceFrame {
private:
    Force force;

public:
    ForceFrame(Force data);
    ~ForceFrame();
    void blit(int position, const Window& window) const;
};


//
class TemperatureFrame {
private:
    Temperature temp;

public:
    TemperatureFrame(Temperature data);
    ~TemperatureFrame();
    void blit(int position, const Window& window) const;
};
