/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include "collectedData.hpp"


CollectedData::CollectedData()
: positions(),
forces(),
temperatures(),
prevPos(0.0),
posNull(0.0),
forceNull(0.0),
changed(false),
saveRepeat(false) {}

void CollectedData::reset() {
    changed = false;
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

void CollectedData::addFrame(float _pos, float _force, Uint16 _temp) {
    // Check, if at new place
    if (positions.size()) {
        if (saveRepeat || _pos != prevPos) {
            addData(_pos, _force, _temp);
        }
    } else {
        addData(_pos, _force, _temp);
    }
}

void CollectedData::addData(float _pos, float _force, Uint16 _temp) {
    positions.add(_pos + posNull);
    forces.add(_force + forceNull);
    temperatures.add(_temp/10.0);

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

float CollectedData::getLastForce() const {
    if (positions.size()) {
        return forces[forces.size()-1];
    }
    return 0.0;
}

float CollectedData::getLastTemp() const {
    if (positions.size()) {
        return temperatures[temperatures.size()-1];
    }
    return 0.0;
}

const BoundedArray<float>& CollectedData::getPositions() const {
    return positions;
}

const BoundedArray<float>& CollectedData::getForces() const {
    return forces;
}

const BoundedArray<float>& CollectedData::getTemperatures() const {
    return temperatures;
}

float CollectedData::getPosNull() const {
    return posNull;
}

float CollectedData::getForceNull() const {
    return forceNull;
}

void CollectedData::setPosNull(float _val) {
    if (positions.size()) {
        positions.offsetBy(_val);
    }
    posNull += _val;
}

void CollectedData::setPosNull() {
    // Setting pos null as last element
    if (positions.size()) {
        setPosNull(-positions[positions.size() - 1]);
    }
}

void CollectedData::setForceNull(float _forceNull) {
    if (forces.size()) {
        forces.offsetBy(_forceNull);
    }
    forceNull += _forceNull;
}

void CollectedData::setForceNullAsLast() {
    // Setting force null as last element
    if (forces.size()) {
        setForceNull(-forces[forces.size() - 1]);
    }
}

void CollectedData::setForceNullAsAvar() {
    // Setting force null as avarage between all
    if (forces.size()) {
        // Finding avarage
        float sumForce = 0.0;
        for (unsigned i=0; i < forces.size(); ++i) {
            sumForce += forces[i];
        }
        setForceNull(-sumForce/forces.size());
    }
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
        SDL_IOprintf(fout, "%.1f; %.3f; %.1f\n", positions[i], forces[i], temperatures[i]);
    }
    changed = false;

    // Closing file
    SDL_CloseIO(fout);
    logger.additional("Program saved to %s", _fileName);
}
