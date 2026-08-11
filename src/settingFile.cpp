/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include <string>
#include "data/initFile.hpp"

// Check if has initfile
#if (USE_SETTING_FILE)

// Files to setup
#include "data/languages.hpp"
#include "app/programming/programMenu.hpp"
#include "menu/targetConnect.hpp"


// Data, load from setting file
void InitFile::loadSettings() {
    // Reading file
    std::ifstream inSettings(SETTING_FILE);
    // Input string line
    std::string currentLine;

    // Reading file until it end
    while (std::getline(inSettings, currentLine)) {
        std::string parameter = currentLine.substr(0, min(currentLine.find(' '), currentLine.find('=')));

        // Switching between options
        if (parameter == "language") {
            std::string lang = getText(currentLine);
            if (lang == "english") {
                LanguagedText::setLanguage(Language::English);
            } else if (lang == "russian") {
                LanguagedText::setLanguage(Language::Russian);
            } /*else if (lang == "german") {
                LanguagedText::setLanguage(Language::German);
            } else if (lang == "belarusian") {
                LanguagedText::setLanguage(Language::Bellarusian);
            }*/
        } /*else if (parameter == "music") {
            audio.music.setVolume(getValue(currentLine) / 100.0f);
        } else if (parameter == "sounds") {
            audio.sounds.setVolume(getValue(currentLine) / 100.0f);
        }*/
    }
    // Closing reading file
    inSettings.close();
}

// Data, saved to setting file
void InitFile::saveSettings() {
    // Creating output file
    std::ofstream outSettings(SETTING_FILE);

    // Writing data with comments to file
    outSettings << "# Settings of indenter app:\n";

    // Writing language
    outSettings << "language = ";
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        outSettings << "english\n";
        break;

    case Language::Russian:
        outSettings << "russian\n";
        break;

    /*case Language::German:
        outSettings << "german\n";
        break;

    case Language::Bellarusian:
        outSettings << "belarusian\n";
        break;*/

    default:
        break;
    }

    // Writing music and sounds volumes
    //outSettings << "music = " << int(audio.music.getVolume()*100) << "\n";
    //outSettings << "sounds = " << int(audio.sounds.getVolume()*100) << "\n";
}

#endif  // (USE_SETTING_FILE)
