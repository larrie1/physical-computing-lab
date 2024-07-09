/*
  Game.hpp - Library for handling the game.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Game_hpp
#define Game_hpp

#include <Player.hpp>
#include <Arduino.h>
#include <Globals.hpp>
#include <Button.hpp>

class Game {
  public:
    inline bool isActive() { return isCurrentlyActive; }

    virtual void setup(GameMode mode, uint8_t highscoreAdress, String name) {
          // reset states
          setAllLow();

          // add players
          for (uint8_t i = 0; i < static_cast<uint8_t>(mode); i++) {
              players[i] = Player(static_cast<Color>(i));
          }

          if (!debug) {
            lcd.clear();
            lcd.noBlink();
            // start animation
            for (uint8_t i = 0; i < DIMENSION; i++) {
              setValueAt(i, Color::BROWN);
              setValueAt(i + 4, Color::BROWN);
              setValueAt(i + 8, Color::BROWN);
              setValueAt(i + 12, Color::BROWN);

              lcd.setCursor(3, 0);
              lcd.print(F("Loading ..."));
              lcd.setCursor(3, 1);
              lcd.print(name);

              for (int j = (i * 5); j < ((i + 1) * 5); j++) {
                lcd.dino(j - 2, 2);
                lcd.setCursor(j - 3, 2);
                lcd.print(F(" "));
                lcd.setCursor(j - 3, 3);
                lcd.print(F(" "));
                if (j == 0 || j == 1) {
                  lcd.setCursor(j - 2, 2);
                  lcd.print(F(" "));
                  lcd.setCursor(j - 2, 3);
                  lcd.print(F(" "));
                  lcd.setCursor(j - 1, 2);
                  lcd.print(F(" "));
                  lcd.setCursor(j - 1, 3);
                  lcd.print(F(" "));
                } else if (j == 19) {
                  lcd.setCursor(j + 1, 2);
                  lcd.print(F(" "));
                  lcd.setCursor(j + 1, 3);
                  lcd.print(F(" "));
                }
                delay(200);
              }
            }
          }

          // reset matrix
          setAllLow();

          isCurrentlyActive = true;
          this->highscoreAdress = highscoreAdress;
          this->mode = mode;
          this->changed = true;
    }

    virtual void loop() {
      // update button list
      double time = update();

      // write current state to matrix
      if (!debug && changed) {
        if (mode == GameMode::MULTIPLAYER && highscoreAdress == 0) {
          lcd.multiPlayerScreen(players[0].getScore(), players[1].getScore(), players[0].getLives(), players[1].getLives());
        } else {
          uint8_t activePlayer = !players[0].isActive && !players[1].isActive ? 0 : players[0].isActive ? 0 : 1;
          lcd.singlePlayerScreen(activePlayer, players[activePlayer].getScore(), players[activePlayer].getLives());
        }
        changed = false;
      }

      double start = millis();

      // check if time is over
      while (Game::isActive() && !changed && (time - (millis() - start)) > 0) {
          // check if button is pressed
          if (!debug) {
              checkReset();
              onPress();
          } else {
              // debug mode
              if (Serial.available() > 0) {
                  char input = Serial.read();
                  checkReset(input);
                  onPress(input);
              }
          }
      }
    }

  protected:
    Player players[MAX_PLAYER];
    bool changed = false;

    uint8_t addRandomButton(int8_t player, long time = BUTTON_TIME) {
      uint8_t index = rand() % BUTTON_COUNT;
      while (buttons[index].getValue() != Color::NONE) {
        // find empty button
        index = rand() % BUTTON_COUNT;
      }
      buttons[index].setValue(static_cast<Color>(player));
      changed = true;
      return index;
    }

    void reset() {
      int8_t bestPlayer = 0;
      // read current highscore
      int8_t highscore = EEPROM.read(highscoreAdress);
      if (players[0].getScore() > players[1].getScore()) {
        // first player won
        bestPlayer = 0;
      } else if (players[0].getScore() < players[1].getScore()) {
        // second player won
        bestPlayer = 1;
      } else if (players[0].getScore() == players[1].getScore() && players[1].getColor() != players[0].getColor()) {
        // draw
        bestPlayer = -1;
      }

      if (bestPlayer != -1 && players[bestPlayer].getScore() > 0) {
        Serial.println("Player " + getPlayerColor(players[bestPlayer].getColor()) + " won with a score of " + String(players[bestPlayer].getScore()) + "!");
      } else if (players[0].getScore() > 0) {
        Serial.println("It's a draw! Both players have a score of " + String(players[0].getScore()) + "!");
      }

      // handle new highscore
      if (players[bestPlayer].getScore() > highscore) {
        EEPROM.write(highscoreAdress, players[bestPlayer].getScore());
        Serial.print(F("New highscore for Game "));
        highscoreAdress == 0 ? Serial.print(F("WhackAMole")) : Serial.print(F("Remember"));
        Serial.println(": " + String(players[bestPlayer].getScore()));
        lcd.highsoreScreen(players[bestPlayer].getScore());
      }

      // reset players
      for (uint8_t i = 0; i < MAX_PLAYER && players[i].getScore() != 0; i++) {
        players[i].reset();
      }

      if (!debug) {
        lcd.resetScreen(bestPlayer, players[bestPlayer].getScore());
      }

      isCurrentlyActive = false;
      setAllLow();
      changed = false;
      isInMenu = true;
      lcd.gameSelect();
      Serial.println(F("Quitting the game ..."));
    }

  private:
    bool isCurrentlyActive = false;
    uint8_t highscoreAdress = 0;
    GameMode mode;

    virtual void onPress(char input = '%') {}

    void checkReset(char input = '%') {
      if ((buttons[0].pressed() && buttons[1].pressed() && buttons[2].pressed() && buttons[3].pressed()) || input == 32) {
        reset();
      }
    }

    double update() {
      double leastRemainingTime = BUTTON_TIME;
      for (int i = 0; i < BUTTON_COUNT; i++) {
        int8_t player = buttons[i].getPlayer();
        double remainingTime = buttons[i].getRemainingTime();
        if (remainingTime < leastRemainingTime) {
          leastRemainingTime = remainingTime;
        }
        if (remainingTime <= 0) {
          changed = true;
          // update score
          players[player].updateScore(-1);
          // Game lost
          if (players[player].getLives() == 0) {
            Serial.println("Player " + getPlayerColor(players[player].getColor()) + " lost!");
            reset();
            // since activeButtons get cleared within reset break the loop here
            break;
          }
          // reset button
          buttons[i].setValue(Color::NONE);
          // add new button
          addRandomButton(player);
        }
      }
      return leastRemainingTime;
    }
};

#endif