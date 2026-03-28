/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"
#include "cycles/baseCycle.hpp"


// Starting cycle
Cycle App::nextCycle = Cycle::Main;

void App::run(Window& _window) {
    logger.additional("\nStart selecting loop");

    // Starting loop of selecting cycles
    while (running) {
        // Selecting new
        switch (nextCycle) {
        case Cycle::Main:
            runCycle<BaseCycle>(_window);
            break;
        
        default:
            break;
        }
    }
}
