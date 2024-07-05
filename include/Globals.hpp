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
#define FIRST_BUTTON_PIN 34

// Red LEDs
#define FIRST_RED_PIN 0

// Green LEDs
#define FIRST_GREEN_PIN 16
/** ----------- PINS END ----------- */


/** ----------- CONSTANS ----------- */
const long START_TIME = 300000L; // 5min in ms
const int SHOW_TIME = 1000;
const int BUTTON_TIME = 3000;
const int MAX_PLAYER = 2;
const int GAMES = 4; // WhackAMole Singleplayer, WhackAMole Multiplayer, Remember Singleplayer, Remember Multiplayer
const int DIMENSION = 4;
const int BUTTON_COUNT = 16;
const bool debug = false;
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
    int8_t buttonIndex = 0;
    if (!debug) {
        for (int i = 2; i < (BUTTON_COUNT * 3) + 3; i += 3) {
            if (i == 20) continue;

            // Button
            int8_t buttonPin = i;
            pinMode(buttonPin, INPUT_PULLUP);

            // Green LED
            int8_t greenPin = i + 1;
            pinMode(i + 1, OUTPUT);
            digitalWrite(i + 1, HIGH);

            // Red LED
            int8_t redPin = i + 2;
            pinMode(redPin, OUTPUT);
            digitalWrite(redPin, HIGH);

            // assign new Button Object
            buttons[buttonIndex] = Button(buttonPin, redPin, greenPin);
            buttonIndex++;
        }
    }
    else
    {
        pinMode(A5, OUTPUT);
        pinMode(A4, OUTPUT);
        buttons[0] = Button(0, A4, A5);
        digitalWrite(A4, HIGH);
        digitalWrite(A5, HIGH);
    }
}

void setAllLow() {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].setValue(Color::NONE);
    }
}

void setValueAt(int8_t index, Color value) {
    buttons[index].setValue(value);
}
/** ----------- FUNCTIONS END ----------- */

#endif