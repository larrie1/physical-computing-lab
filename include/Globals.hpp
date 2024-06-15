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
#include <EEPROM.h>
#include <Lcd.hpp>

/** ----------- PINS ----------- */
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


/** ----------- CONSTANS ----------- */
const long START_TIME = 300000L; // 5min in ms
const int SHOW_TIME = 1000;
const int BUTTON_TIME = 3000;
const int MAX_PLAYER = 2;
const int GAMES = 4; // WhackAMole Singleplayer, WhackAMole Multiplayer, Remember Singleplayer, Remember Multiplayer
const int DIMENSION = 4;
const int REGISTER_COUNT = 2;
const int BUTTON_COUNT = 16;
const bool debug = true;
const char buttonMap[BUTTON_COUNT] = {'1', '2', '3', '4', 'q', 'w', 'e', 'r', 'a', 's', 'd', 'f', 'y', 'x', 'c', 'v'};

// non constants
RgbMatrix<DIMENSION> matrix = RgbMatrix<DIMENSION>();
ShiftIn<REGISTER_COUNT> shift = ShiftIn<REGISTER_COUNT>();
bool isInMenu = true;
Lcd lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
/** ----------- CONSTANS END ----------- */


/** ----------- ENUMS ----------- */
enum class GameMode {
    SINGLEPLAYER = 1,
    MULTIPLAYER = 2,
    UNKNOWN = 3
};
/** ----------- ENUMS END ----------- */


/** ----------- FUNCTIONS ----------- */
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
/** ----------- FUNCTIONS END ----------- */

#endif