/*
  Gloabls.hpp - Library for handling global variables and constans.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Globals_hpp
#define Globals_hpp

#include <Arduino.h>
#include <ShiftIn.h>
#include <RgbMatrix.h>

/** ----------- CONSTANS ----------- */
#define START_TIME 300000 // 5min in ms
#define WRONG_PRESSES_THRESHHOLD 1
#define SHOW_TIME 1000
#define BUTTON_TIME 3000
#define BUTTON_COUNT 16

#define MAX_PLAYER 2
#define PLAYER_1 0
#define PLAYER_2 1
#define GAMES 4 // WhackAMole Singleplayer, WhackAMole Multiplayer, Remember Singleplayer, Remember Multiplayer
#define DIMENSION 4
#define REGISTER_COUNT 2
#define BUTTON_COUNT 16
/** ----------- CONSTANS END ----------- */

/** ----------- PINS ----------- */
#define START_BUTTON_PIN  1
#define MODE_BUTTON_PIN 2
#define BUTTON_COUNT 16

// Buttons
#define BUTTON_LOAD_PIN 1
#define BUTTON_CLOCK_ENABLE_PIN 2
#define BUTTON_DATA_PIN 3
#define BUTTON_CLOCK_PIN 4

// Red LEDs
#define RED_LATCH_PIN 7
#define RED_DATA_PIN 8

// Green LEDs
#define GREEN_LATCH_PIN 10
#define GREEN_DATA_PIN 11

// Blue LEDs
#define BLUE_LATCH_PIN 13
#define BLUE_DATA_PIN 14

// Clock
#define CLOCK_PIN 6
/** ----------- PINS END ----------- */

enum class GameMode {
    SINGLEPLAYER = 1,
    MULTIPLAYER = 2,
    UNKNOWN = 3
};

/** ----------- VARIABLES ----------- */
extern RgbMatrix<DIMENSION> matrix;
extern ShiftIn<REGISTER_COUNT> shift;
extern const bool debug;
extern const char buttonMap[16];
extern bool isInMenu;
/** ----------- VARIABLES END ----------- */

String getPlayerColor(Color color) {
        switch (color) {
            case Color::RED:
                return "RED";
            case Color::GREEN:
                return "GREEN";
            case Color::BLUE:
                return "BLUE";
            default:
                return "UNKNOWN";
        }
    }

#endif