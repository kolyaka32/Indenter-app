/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "settingsMenu.hpp"
#include "../data/cycleTemplate.hpp"
#include "../app/output/collectedData.hpp"


SettingsMenu::SettingsMenu(const Window& _window)
: SubWindow(_window, 0.5, 0.5, 0.42, 0.75),
settingButton{_window, 0.97, 0.045, 0.04, Textures::SettingsButton},
//titleText{window, 0.5, 0.13, {"Pause", "Пауза", "Pause", "Паўза"},
//    2, GUI::Aligment::Midle, Height::Info},
titleText{_window, 0.5, 0.16, {"Pause", "Пауза"},
    2, GUI::Aligment::Midle, Height::Title},
flags {
    {_window, 0.4, 0.3, 0.16, Textures::FlagUSA},
    {_window, 0.6, 0.3, 0.16, Textures::FlagRUS},
    //{_window, 0.35, 0.45, 0.25, Textures::FlagGER},
    //{_window, 0.65, 0.45, 0.25, Textures::FlagBEL},
},
#if (PRELOAD_MUSIC)
musicText{_window, 0.5, 0.58, {"Music", "Музыка", "Die Musik", "Музыка"}, 1},
musicSlider{_window, 0.5, 0.64, 0.5, audio.music.getVolume()},
#endif
#if (PRELOAD_SOUNDS)
soundText{_window, 0.5, 0.7, {"Sounds", "Звуки", "Geräusche", "Гук"}, 1},
soundSlider{_window, 0.5, 0.76, 0.5, audio.sounds.getVolume()},
#endif
creditTitle(_window, 0.5, 0.48, {"About", "О приложении"}, 2, GUI::Aligment::Midle, Height::Info),
creditText(_window, 0.5, 0.52, {"\"Indenter\" app", "Приложение \"индентер\""}, 1, GUI::Aligment::Midle, Height::SubTitle),
creditLicense(_window, 0.5, 0.55, {"Distributed under a license GNU GPL v3.0",
    "Распространяется по лицензии GNU GPL v3.0"}, 1),
creditCopyright(_window, 0.5, 0.58, {"© 2026. BMSTU,", "© 2026. МГТУ им. Баумана,"}, 1),
creditCathedra(_window, 0.5, 0.61, {"department \"Robotics and integrated automation\"",
    "кафедра \"Робототехника и комплексная автоматизация\""}, 1),
//exitButton{_window, 0.5, 0.82, {"Close", "Закрыть", "Ausfahrt", "Выхад"}}
resetButton(_window, 0.5, 0.72, {"Reset data", "Очистить данные"}),
exitButton{_window, 0.5, 0.78, {"Exit from app", "Выйти из приложения"}},
closeButton{_window, 0.5, 0.84, {"Close", "Закрыть"}}
{}

bool SettingsMenu::click(const Mouse _mouse) {
    // Check, if click on setting butoon
    if (settingButton.in(_mouse)) {
        toggle();
        return true;
    }
    // Clicking in menu
    if (active) {
        if (exitButton.in(_mouse)) {
            App::setNextCycle(Cycle::None);
            CycleTemplate::stop();
            close();
            return true;
        }
        if (closeButton.in(_mouse)) {
            close();
            return true;
        }
        if (resetButton.in(_mouse)) {
            collectedData.reset();
            return true;
        }
        // Check on changing language
        for (unsigned i = 0; i < (unsigned)Language::Count; ++i) {
            if (flags[i].in(_mouse)) {
                if (LanguagedText::setLanguage((Language)i)) {
                    // Changing language
                    window.updateTitle();
                    // Restarting game
                    CycleTemplate::restart();
                    return true;
                }
            }
        }
        // Resetting holding object
        holdingSlider = 0;
        #if (PRELOAD_MUSIC)
        if (musicSlider.in(_mouse)) {
            holdingSlider = 1;
            return true;
        }
        #endif
        #if (PRELOAD_SOUNDS)
        if (soundSlider.in(_mouse)) {
            holdingSlider = 2;
            return true;
        }
        #endif
        return true;
    }
    return false;
}

void SettingsMenu::unClick() {
    if (active) {
        // Resetting selected box
        holdingSlider = 0;
    }
}

bool SettingsMenu::scroll(const Mouse _mouse, float _wheelY) {
    if (active) {
        // Checking scroll on sliders
        #if (PRELOAD_MUSIC)
        if (musicSlider.in(_mouse)) {
            audio.music.setVolume(musicSlider.scroll(_wheelY));
            return true;
        }
        #endif
        #if (PRELOAD_SOUNDS)
        if (soundSlider.in(_mouse)) {
            audio.sounds.setVolume(soundSlider.scroll(_wheelY));
            return true;
        }
        #endif
        return true;
    }
    return false;
}

void SettingsMenu::update() {
    if (active) {
        // Creating and finding mouse position
        Mouse mouse;
        mouse.updatePos();

        // Updating pressing on sliders
        switch (holdingSlider) {
        // Music slier
        #if (PRELOAD_MUSIC)
        case 1:
            audio.music.setVolume(musicSlider.setValue(mouse.getX()));
            break;
        #endif

        // Sound slider
        #if (PRELOAD_SOUNDS)
        case 2:
            // Updating sound slider state
            audio.sounds.setVolume(soundSlider.setValue(mouse.getX()));

            // Playing sound effect for understanding loud
            if (getTime() > nextSound) {
                audio.sounds.play(Sounds::SliderSound);
                nextSound = getTime() + 400;
            }
            break;
        #endif

        default:
            break;
        }
    }
}

void SettingsMenu::blit() const {
    // Draw pause button
    settingButton.blit();

    // Drawing menu if need
    if (active) {
        background.blit();
        titleText.blit();

        // Blitting language buttons
        for (unsigned i = 0; i < unsigned(Language::Count); ++i) {
            flags[i].blit();
        }
        // Music slider
        #if (PRELOAD_MUSIC)
        musicText.blit();
        musicSlider.blit();
        #endif
        // Sound slier
        #if (PRELOAD_SOUNDS)
        soundSlider.blit();
        soundText.blit();
        #endif
        // Credits
        creditTitle.blit();
        creditText.blit();
        creditLicense.blit();
        creditCathedra.blit();
        creditCopyright.blit();
        // Additional buttons
        resetButton.blit();
        exitButton.blit();
        closeButton.blit();
    }
}
