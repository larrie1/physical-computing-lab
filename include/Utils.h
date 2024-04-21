/*
  Utils.h - Library for handling the utilities.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Utils_h
#define Utils_h

int random();
int randInRange(int min, int max);
void initRegister(int shiftPin, int storePin, int dataPin);
int readRegisterAt(int shiftPin, int dataPin, int index);
void writeRegisterAt(int shiftPin, int storePin, int dataPin, int index);

#endif