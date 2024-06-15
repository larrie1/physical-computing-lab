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

    void multiPlayerScreen() {
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
        print(F("Green"));
    }
};

#endif