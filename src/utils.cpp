#include <Utils.h>

int randInRange(int min, int max) {
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) );
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

int random() {
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
  digitalWrite(storePin, HIGH)
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

void writeRegisterAt(int shiftPin, int storePin, int dataPin, int index) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        digitalWrite(shiftPin, LOW);

        if (i == index) {
            digitalWrite(dataPin, HIGH);
        }

        digitalWrite(shiftPin, HIGH);
    }
    digitalWrite(storePin, HIGH)
}