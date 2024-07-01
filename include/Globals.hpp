/*
  Gloabls.hpp - Library for handling global variables and constans.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Globals_hpp
#define Globals_hpp

#include <Arduino.h>
#include <EEPROM.h>
#include <Lcd.hpp>
#include <Button.hpp>

/** ----------- PINS ----------- */
// Buttons
#define FIRST_BUTTON_PIN 1

// Red LEDs
#define FIRST_RED_PIN 17

// Green LEDs
#define FIRST_GREEN_PIN 34
/** ----------- PINS END ----------- */


/** ----------- CONSTANS ----------- */
const long START_TIME = 300000L; // 5min in ms
const int SHOW_TIME = 1000;
const int BUTTON_TIME = 3000;
const int MAX_PLAYER = 2;
const int GAMES = 4; // WhackAMole Singleplayer, WhackAMole Multiplayer, Remember Singleplayer, Remember Multiplayer
const int DIMENSION = 4;
const int BUTTON_COUNT = 16;
const bool debug = true;
const char buttonMap[BUTTON_COUNT] = {'1', '2', '3', '4', 'q', 'w', 'e', 'r', 'a', 's', 'd', 'f', 'y', 'x', 'c', 'v'};

// non constants
Button buttons[BUTTON_COUNT] = {};
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
        case Color::BROWN:
            return "BROWN";
        default:
            return "UNKNOWN";
    }
}

void assignPins() {
    if (!debug) {
        for (int i = 0; i < BUTTON_COUNT; i++) {
        pinMode(FIRST_BUTTON_PIN + i, INPUT_PULLUP);
        pinMode(FIRST_RED_PIN + i, OUTPUT);
        pinMode(FIRST_GREEN_PIN + i, OUTPUT);
        buttons[i] = Button(FIRST_BUTTON_PIN + i, FIRST_RED_PIN + i, FIRST_GREEN_PIN + i);
        digitalWrite(FIRST_RED_PIN + i, HIGH);
        digitalWrite(FIRST_GREEN_PIN + i, HIGH);
        }
    } else {
        pinMode(A5, OUTPUT);
        pinMode(A4, OUTPUT);
        buttons[0] = Button(0, A4, A5);
        digitalWrite(A4, HIGH);
        digitalWrite(A5, HIGH);
    }
}

void setAllLow() {
    for (Button button : buttons) {
        button.setValue(Color::NONE);
    }
}

void setValueAt(int8_t index, Color value) {
    buttons[index].setValue(value);
}
/** ----------- FUNCTIONS END ----------- */

#endif