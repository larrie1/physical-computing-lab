/*
  Utils.h - Library for handling the utilities.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Utils_h
#define Utils_h

#include <Arduino.h>

enum class Color {
  RED,
  GREEN,
  BLUE
};

int randomButton();
int randInRange(int min, int max);
int* randomButtonList(int size);
void initRegister(int clockPin, int latchPin, int dataPin);
int readRegisterAt(int clockPin, int dataPin, int index);
void writeRegisterAt(int clockPin, int latchPin, int dataPin, int index, int value);
long readButtons(int loadPin, int clockPin, int clockEnablePin, int dataPin);
void writeToLed(int clockPin, int latchPin, int dataPin, long data);
void resetLed(int clockPin, int latchPin, int dataPin);
long randomBits(int length);
long *randomBitsList(int length);

#endif