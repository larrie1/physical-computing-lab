/*
  Player.hpp - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Button_hpp
#define Button_hpp

#include <Stopwatch.h>
#include <Arduino.h>

enum class Color {
  RED = 0,
  GREEN = 1,
  BROWN = 2,
  NONE = 3
};

class Button {
  public:
        // Default constructor
        Button() : value(Color::NONE), pin(0), redPin(0), greenPin(0) {}

        Button(int8_t pin, int8_t redPin, int8_t greenPin) : value(Color::NONE), pin(pin), redPin(redPin), greenPin(greenPin) {}

        inline Color getValue() { return value; }
        inline void startWatch() { watch.start(); }
        inline void stopWatch() { watch.stop(); }
        inline int getPlayer() { return static_cast<int>(value); }
        inline bool pressed() { return digitalRead(pin) == HIGH; }

        void setValue(Color value) {
          this->value = value;
          switch (this->value) {
            case Color::RED:
              digitalWrite(redPin, LOW);
              digitalWrite(greenPin, HIGH);
              watch.start();
              break;

            case Color::GREEN:
              digitalWrite(greenPin, LOW);
              digitalWrite(redPin, HIGH);
              watch.start();
              break;
            
            case Color::BROWN:
              digitalWrite(redPin, LOW);
              digitalWrite(greenPin, LOW);
              watch.start();
              break;

            default:
              digitalWrite(redPin, HIGH);
              digitalWrite(greenPin, HIGH);
              watch.stop();
              break;
          }
        }

        double getRemainingTime() {
            double elapsed = time - watch.elapsedMilliseconds();
            if (elapsed <= 0) {
                watch.stop();
                return 0;
            }
            return elapsed;
        }

  private:
    Color value;
    int8_t pin;
    int8_t redPin;
    int8_t greenPin;
    double time = 3000;
    Stopwatch watch = Stopwatch();
};

#endif