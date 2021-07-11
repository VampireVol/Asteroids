# Asteroids
![Logo](./image/logo.jpg)
## Translations
- [English](./README.md)
- [Russian](./README_ru.md)
## Gameplay
![Gameplay](./image/gameplay.gif)
## Description
Created a variant of the game Asteroids using the original framework. The goal of the game is to destroy asteroids while player driving a spaceship and to score as many points as possible until lose. Game starting after press any button. The player initially has 3 lives. For every 10.000 points player is added one life, also possible to resurrect after death, if the last shots earn an extra life. After losing a life, the player becomes invulnerable for 5 seconds. Next level occurs after the destruction of all asteroids on the level.
Asteroids are divided into 3 types:
Size | Hits for destruction | Score
--- | --- | ---
Large | 3 | 300
Medium | 2 | 200
Small | 1 | 100

When hit by an asteroid, its boundaries darken. When a large or medium asteroid is destroyed, two smaller asteroids appear in place of the destroyed one.
## Control
### Keyboard
- W or Up arrow - thrust
- A or Left arrow - turn left
- D or Right arrow - turn right
- Space - shoot
- Esc - exit
- P - pause
- Enter - reset game progress
### Gamepad (xinput)
- DPad Up or RT - thrust
- DPad Left or LS Left - turn left
- DPad Right or LS Right - turn right
- A - shoot
- Back - exit
- Start - pause
- Press RS (R3) - reset game progress
## Install
### Windows
1. Download last [build](https://github.com/VampireVol/Asteroids/releases)
2. Extract .zip archive
3. Execute GameTemplate.exe
## Build information
Build tools: Visual Studio 2019 (v142)