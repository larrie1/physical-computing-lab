#include <Utils.h>

int randInRange(int min, int max) {
   return min + rand() % (( max + 1 ) - min);
}

int randomButton() {
    return randInRange(0, 16);
}

void initRegister(int shiftPin, int storePin, int dataPin) {
  pinMode(storePin, OUTPUT);
  pinMode(shiftPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < BUTTON_COUNT; i++) {
    // set shift pin to "wait"
    digitalWrite(shiftPin, LOW);

    // writing to data pin
    digitalWrite(dataPin, LOW);

    // rising slope -> shifting data in the register
    digitalWrite(shiftPin, HIGH);
  }

  // write whole register to output
  digitalWrite(storePin, HIGH);
}

int readRegisterAt(int shiftPin, int dataPin, int index) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        digitalWrite(shiftPin, LOW);

        if (i == index) {
            return digitalRead(dataPin);
        }

        digitalWrite(shiftPin, HIGH);
    }
    return 0;
}

void writeRegisterAt(int shiftPin, int storePin, int dataPin, int index, int value) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        digitalWrite(shiftPin, LOW);

        if (i == index) {
            digitalWrite(dataPin, value);
        }

        digitalWrite(shiftPin, HIGH);
    }
    digitalWrite(storePin, HIGH);
}

void toggleLightAt(Color color, int index) {
    switch (color) {
    case Color::RED:
        writeRegisterAt(RED_SHIFT_PIN, RED_STORE_PIN, RED_DATA_PIN, index);
        break;
    case Color::GREEN:
        writeRegisterAt(GREEN_SHIFT_PIN, GREEN_STORE_PIN, GREEN_DATA_PIN, index);
        break;
    case Color::BLUE:
        writeRegisterAt(BLUE_SHIFT_PIN, BLUE_STORE_PIN, BLUE_DATA_PIN, index);
        break;
    
    default:
        break;
    }
}