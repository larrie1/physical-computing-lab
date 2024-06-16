/*
  Lcd.hpp - Library for handling the Lcd Display.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Lcd_hpp
#define Lcd_hpp

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Lcd : public LiquidCrystal_I2C {
  public:
    Lcd(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows) {}

    void init() {
        // LCD initialization
        LiquidCrystal_I2C::init();
        LiquidCrystal_I2C::clear();
        backlight();
        home();

        createChar(0, dino0);
        createChar(1, dino1);
        createChar(2, dino2);
        createChar(3, dino3);
        createChar(4, dino4);
        createChar(5, dino5);
        createChar(6, dino6);
        createChar(7, heart);
    }

    void clear() {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 20; col++) {
                setCursor(col, row);
                print(F(" "));
            }
        }
    }

    void startScreen() {
        clear();
        setCursor(0, 0);
        print(F("####################"));
        setCursor(0, 1);
        print(F("#   Game Console   #"));
        setCursor(0, 2);
        print(F("#   by GridGurus   #"));
        setCursor(0, 3);
        print(F("####################"));
    }

    void gameSelect() {
        clear();
        setCursor(0, 0);
        print(F(" Whack-A-Mole 1     "));
        setCursor(0, 1);
        print(F(" Whack-A-Mole 2     "));
        setCursor(0, 2);
        print(F(" Remember 1         "));
        setCursor(0, 3);
        print(F(" Remember 2         "));
    }

    void dino(int x, int y) {
        setCursor(x, y);
        write(byte(0));
        setCursor(x + 1, y);
        write(byte(1));
        setCursor(x + 2, y);
        write(byte(2));
        setCursor(x + 3, y);
        write(byte(3));
        setCursor(x, y + 1);
        write(byte(4));
        setCursor(x + 1, y + 1);
        write(byte(5));
        setCursor(x + 2, y + 1);
        write(byte(6));
    }

    void highsoreScreen(int8_t highscore) {
        clear();
        setCursor(5, 1);
        print(F("Highscore!"));
        setCursor(9, 2);
        print(highscore);
        noBacklight();
        delay(100);
        backlight();
        delay(100);
        noBacklight();
        delay(100);
        backlight();
        delay(100);
        noBacklight();
        delay(100);
        backlight();
        delay(3000);
    }

    void resetScreen(int8_t player, int8_t score) {
        clear();
        setCursor(5, 0);
        print(F("GAME OVER"));
        setCursor(1, 2);
        blink();
        uint8_t cursorX = 1;
        if (player == -1) {
            print(F("I"));
            delay(200);
            setCursor(2, 2);
            print(F("t"));
            delay(200);
            setCursor(3, 2);
            print(F("'"));
            delay(200);
            setCursor(4, 2);
            print(F("s"));
            delay(200);
            setCursor(5, 2);
            print(F(" "));
            delay(200);
            setCursor(6, 2);
            print(F("a"));
            delay(200);
            setCursor(7, 2);
            print(F(" "));
            delay(200);
            setCursor(8, 2);
            print(F("d"));
            delay(200);
            setCursor(9, 2);
            print(F("r"));
            delay(200);
            setCursor(10, 2);
            print(F("a"));
            delay(200);
            setCursor(11, 2);
            print(F("w"));
            delay(200);
            setCursor(12, 2);
            print(F("!"));
            delay(200);
            setCursor(13, 2);
            delay(1000);
        } else {
            if (player == 0) {
                print(F("R"));
                delay(200);
                setCursor(2, 2);
                print(F("E"));
                delay(200);
                setCursor(3, 2);
                print(F("D"));
                delay(200);
                cursorX = 4;
            } else {
                print(F("G"));
                delay(200);
                setCursor(2, 2);
                print(F("R"));
                delay(200);
                setCursor(3, 2);
                print(F("E"));
                delay(200);
                setCursor(4, 2);
                print(F("E"));
                delay(200);
                setCursor(5, 2);
                print(F("N"));
                delay(200);
                cursorX = 6;
            }
            setCursor(cursorX, 2);
            print(F(" "));
            delay(200);
            setCursor(cursorX + 1, 2);
            print(F("w"));
            delay(200);
            setCursor(cursorX + 2, 2);
            print(F("o"));
            delay(200);
            setCursor(cursorX + 3, 2);
            print(F("n"));
            delay(200);
            setCursor(cursorX + 4, 2);
            print(F("!"));
            delay(200);
            setCursor(cursorX + 5, 2);
            delay(1000);
        }
    }

    void showScreen(uint8_t player) {
        clear();
        setCursor(2, 1);
        print(F("Try to Remember!"));
        setCursor(2, 2);
        if (player == 0) {
            print(F("RED"));
        } else if (player == 1) {
            print(F("GREEN"));
        } else {
            print(F("BLUE"));
        }
    }

    void singlePlayerScreen(int8_t player, int8_t score, int8_t lives) {
        clear();
        noBlink();
        setCursor(6, 0);
        if (player == 0) {
            print(F("RED"));
        } else if (player == 1) {
            print(F("GREEN"));
        } else {
            print(F("BLUE"));
        }
        setCursor(6, 1);
        print(F("Score: "));
        setCursor(13, 1);
        print(score);
        for (int i = 0; i < lives; i++) {
            setCursor(i + 6, 2);
            write(byte(7));
        }
    }

    void multiPlayerScreen(int8_t score1, int8_t score2, int8_t lives1, int8_t lives2) {
        clear();
        noBlink();
        setCursor(10, 0);
        print("|");
        setCursor(10, 1);
        print("|");
        setCursor(10, 2);
        print("|");
        setCursor(10, 3);
        print("|");
        setCursor(3, 0);
        print(F("RED"));
        setCursor(13, 0);
        print(F("GREEN"));
        setCursor(0, 1);
        print(F("Score: "));
        setCursor(7, 1);
        print(score1);
        setCursor(11, 1);
        print(F("Score: "));
        setCursor(18, 1);
        print(score2);
        for (int i = 0; i < lives1; i++) {
            setCursor(i, 2);
            write(byte(7));
        }
        for (int i = 0; i < lives2; i++) {
            setCursor(i + 11, 2);
            write(byte(7));
        }
    }

    private:
        byte dino0[8] = {
            B00000,
            B00000,
            B00000,
            B10000,
            B10000,
            B10000,
            B11000,
            B11100,
        };

        byte dino1[8] = {
            B00000,
            B00001,
            B00001,
            B00001,
            B00001,
            B00011,
            B01111,
            B11111,
        };

        byte dino2[8] = {
            B11111,
            B10111,
            B11111,
            B11111,
            B11100,
            B11111,
            B11100,
            B11100,
        };

        byte dino3[8] = {
            B10000,
            B11000,
            B11000,
            B11000,
            B00000,
            B10000,
            B00000,
            B00000,
        };

        byte dino4[8] = {
            B11111,
            B11111,
            B01111,
            B00111,
            B00011,
            B00011,
            B00010,
            B00011,
        };

        byte dino5[8] = {
            B11111,
            B11111,
            B11111,
            B11111,
            B10110,
            B00010,
            B00010,
            B00011,
        };

        byte dino6[8] = {
            B11111,
            B11001,
            B10000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
        };

        byte heart[8] = {
            B00000,
            B00000,
            B11011,
            B11111,
            B11111,
            B01110,
            B00100,
            B00000,
        };
};

#endif