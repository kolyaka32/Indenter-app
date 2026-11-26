/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"


CollectedData::CollectedData()
: time(),
positions(),
forces(),
temperatures(),
prevPos(0.0),
changed(false),
saveRepeat(false) {}

void CollectedData::reset() {
    changed = false;
    time.reset();
    positions.reset();
    forces.reset();
    temperatures.reset();
}

CollectedData::~CollectedData() {
    // Check, if not saved
    if (changed) {
        trySave("data");
    }
}

void CollectedData::addFrame(Uint32 _time, float _pos, float _force, Uint16 _temp) {
    // Check, if at new place
    if (positions.size()) {
        if (saveRepeat || _pos != prevPos) {
            addData(_time, _pos, _force, _temp);
        }
    } else {
        addData(_time, _pos, _force, _temp);
    }
}

void CollectedData::addData(Uint32 _time, float _pos, float _force, Uint16 _temp) {
    time.add(_time/1000.0f);
    positions.add(_pos);
    forces.add(_force);
    temperatures.add(_temp/10.0f);

    // Set that changed
    prevPos = _pos;
    changed = true;
}

bool CollectedData::isChanged() const {
    return changed;
}

unsigned CollectedData::getLineCount() const {
    return positions.size();
}

void CollectedData::setPosNullAsLast() {
    positions.offsetBy(-positions.last());
}

void CollectedData::setForceNullAsLast() {
    forces.offsetBy(-forces.last());
}

void CollectedData::setForceNullAsAvar() {
    forces.offsetBy(-forces.avr());
}

void CollectedData::trySave(const char* _name) {
    // Find avaliable name
    char buffer[100];
    int number = 1;
    SDL_PathInfo info;

    do {
        // Create new name
        SDL_snprintf(buffer, sizeof(buffer), "records\\%s-%d.csv", _name, number);
        number++;

        // Check if file already exist
    } while (SDL_GetPathInfo(buffer, &info));

    // Saving to file
    save(buffer);
}

void CollectedData::save(const char* _fileName) {
    // Open file
    SDL_IOStream* fout = SDL_IOFromFile(_fileName, "w");
    if (fout == nullptr) {
        return;
    }

    // Write data
    for (unsigned i=0; i < positions.size(); ++i) {
        SDL_IOprintf(fout, "%4d %.2f %.1f; %.3f; %.1f\n", i, time[i], positions[i], forces[i], temperatures[i]);
    }
    changed = false;

    // Closing file
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", _fileName);
}
