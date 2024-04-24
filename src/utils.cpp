#include <Utils.h>

int randInRange(int min, int max) {
   return min + rand() % (( max + 1 ) - min);
}

int randomButton() {
    return randInRange(0, 16);
}

long randomBits(int length) {
    long result = 0;
    for (int i = 0; i < length; ++i) {
        // Shift the current bits to the left by 1
        result <<= 1;
        
        // Set the least significant bit to a random value (0 or 1)
        result |= rand() & 1;
    }
    return result;
}

long* randomBitsList(int length) {
    long *list = new long[length];
    for (int i = 0; i < length; i++) {
        list[i] = randomBits(16);
    }
    return list;
}

int* randomButtonList(int size) {
    int* list = new int[size];
    for (int i = 0; i < size; i++) {
        list[i] = randomButton();
    }
    return list;
}

void initRegister(int clockPin, int latchPin, int dataPin) {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, LOW);
    /*for (int i = 0; i < BUTTON_COUNT; i++) {
      // set shift pin to "wait"
      digitalWrite(shiftPin, LOW);

      // writing to data pin
      digitalWrite(dataPin, LOW);

      // rising slope -> shifting data in the register
      digitalWrite(shiftPin, HIGH);
    }*/

    // write whole register to output
    digitalWrite(latchPin, HIGH);
}

// get data from register at index 
int readRegisterAt(int clockPin, int dataPin, int index) {
    for (int i = 0; i < 16; i++) {
        digitalWrite(clockPin, LOW);

        if (i == index) {
            return digitalRead(dataPin);
        }

        digitalWrite(clockPin, HIGH);
    }
    return 0;
}

// write to register at index the vale 
void writeRegisterAt(int clockPin, int latchPin, int dataPin, int index, int value) {
    for (int i = 0; i < 16; i++) {
        digitalWrite(clockPin, LOW);

        if (i == index) {
            digitalWrite(dataPin, value);
        }

        digitalWrite(clockPin, HIGH);
    }
    digitalWrite(latchPin, HIGH);
}

uint8_t getBinary(int index[], int length) {
  uint8_t binary = 0;
  for (int i = 0; i < length; i++) {
    binary = binary | 1 << index[i];
  }
  return binary;
}

// read data of all Buttons
long readButtons(int loadPin, int clockPin, int clockEnablePin, int dataPin) {
    // Write pulse to load pin
    digitalWrite(loadPin, LOW);
    delayMicroseconds(5);
    digitalWrite(loadPin, HIGH);
    delayMicroseconds(5);
 
    // Get data 
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockEnablePin, LOW);
    uint8_t incoming = shiftIn(dataPin, clockPin, LSBFIRST);
    digitalWrite(clockEnablePin, HIGH);

    // invert the result
    return ~incoming;
}

// write the data to LED
void writeToLed(int clockPin, int latchPin, int dataPin, long data) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, data);
  digitalWrite(latchPin, HIGH);
}

void resetLed(int clockPin, int latchPin, int dataPin) {
    writeToLed(clockPin, latchPin, dataPin, LOW);
}