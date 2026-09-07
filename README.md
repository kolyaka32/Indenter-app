# The "Indenter" app on C++ using SDL3
[![en](https://img.shields.io/badge/lang-en-green.svg)](https://github.com/kolyaka32/Indenter-app/blob/main/README.md)  [![ru](https://img.shields.io/badge/lang-ru-green.svg)](https://github.com/kolyaka32/Indenter-app/blob/main/README-ru.md)

This codebase implement specialised program for control of own developed "indenter" tool

![Screenshot of app](/screenshots/main-en.png?raw=true)


## Usage
This is specialised app for controlling "indenter" tool - special instrument for getting physical parameters of reserched material. For that this program allows to select port with [connected tool](https://github.com/kolyaka32/Indenter-controller) itself. After that program start collecting data from it and draw it on screen with corresponding positions. As control it could move measuring head with settuped speed. For easier and automated measures program has it own interpretable pseudo-programming language. For better interactions with it has save/load system (which also work between sessions). As as result of work you can export table in .csv format.


## Supported languages
* English
* Russian


## Supported platforms
* Windows (7+)
* Unix (in development)


## Launching
Download archieve from [releases](https://github.com/kolyaka32/Indenter-app/releases), depend on platform, unzip and run 'Indenter.exe'/'Indenter'!


## Used external libraries:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/nih-at/libzip
