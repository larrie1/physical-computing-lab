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
          matrix.setAllLow();

          // add players
          for (uint8_t i = 0; i < static_cast<uint8_t>(mode); i++) {
              players[i] = Player(static_cast<Color>(i));
          }

          lcd.clear();
          lcd.noBlink();
          // start animation
          for (uint8_t i = 0; i < DIMENSION; i++) {
            matrix.set(Color::BLUE, i, HIGH);
            matrix.set(Color::BLUE, i + 4, HIGH);
            matrix.set(Color::BLUE, i + 8, HIGH);
            matrix.set(Color::BLUE, i + 12, HIGH);
            matrix.write(Color::BLUE, false);

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

          // reset matrix
          matrix.writeAllLow();

          isCurrentlyActive = true;
          this->highscoreAdress = highscoreAdress;
          this->mode = mode;
    }

    virtual void loop() {
      // update button list
      double time = update();

      // write current state to matrix
      if (changed) {
        if (mode == GameMode::MULTIPLAYER && highscoreAdress == 0) {
          lcd.multiPlayerScreen(players[0].getScore(), players[1].getScore(), players[0].getLives(), players[1].getLives());
        } else {
          uint8_t activePlayer = !players[0].isActive && !players[1].isActive ? 0 : players[0].isActive ? 0 : 1;
          lcd.singlePlayerScreen(activePlayer, players[activePlayer].getScore(), players[activePlayer].getLives());
        }
        matrix.writeAll(true);
        changed = false;
      }

      double start = millis();

      // check if time is over
      while (Game::isActive() && !changed && (time - (millis() - start)) > 0) {
          // check if button is pressed
          if (!debug && shift.update()) {
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
    Button activeButtons[BUTTON_COUNT];
    uint8_t level = 1;
    bool changed = false;

    uint8_t addRandomButton(int8_t player, long time = BUTTON_TIME) {
      uint8_t buttonIndex = rand() % (BUTTON_COUNT - 1);
      int8_t arrayIndex = -1;
      uint8_t counter = 0;
      while (counter < BUTTON_COUNT) {
        // find empty button
        if (activeButtons[counter].getPlayer() == -1 && arrayIndex == -1) {
          arrayIndex = counter;
        } else if (activeButtons[counter].getIndex() == buttonIndex) {
          buttonIndex = random(0, BUTTON_COUNT);
          counter = 0;
        }
        counter++;
      }
      activeButtons[arrayIndex] = Button(buttonIndex, player, time);
      changed = true;
      return buttonIndex;
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
          
      // reset buttons
      for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
          activeButtons[i].remove();
      }

      lcd.resetScreen(bestPlayer, players[bestPlayer].getScore());

      isCurrentlyActive = false;
      level = 1;
      matrix.writeAllLow();
      changed = false;
      isInMenu = true;
      lcd.gameSelect();
      lcd.blink();
      Serial.println(F("Quitting the game ..."));
    }

  private:
    bool isCurrentlyActive = false;
    uint8_t highscoreAdress = 0;
    GameMode mode;

    virtual void onPress(char input = '%') {}

    void checkReset(char input = '%') {
      if ((shift.pressed(0) && shift.pressed(1) && shift.pressed(2) && shift.pressed(3)) || input == 32) {
        reset();
      }
    }

    double update() {
      matrix.setAllLow();
      double leastRemainingTime = BUTTON_TIME;
      for (uint8_t i = 0; activeButtons[i].getPlayer() != -1 && i < BUTTON_COUNT; i++) {
        double remainingTime = activeButtons[i].getRemainingTime();
        if (remainingTime < leastRemainingTime) {
          leastRemainingTime = remainingTime;
        }
        if (remainingTime > 0) {
          // set led for player on
          matrix.set(players[activeButtons[i].getPlayer()].getColor(), activeButtons[i].getIndex(), HIGH);
        } else {
          changed = true;
          // update score
          players[activeButtons[i].getPlayer()].updateScore(-1);
          // Game lost
          if (players[activeButtons[i].getPlayer()].getLives() == 0) {
            Serial.println("Player " + getPlayerColor(players[activeButtons[i].getPlayer()].getColor()) + " lost!");
            reset();
            // since activeButtons get cleared within reset break the loop here
            break;
          }
          int8_t player = activeButtons[i].getPlayer();
          // remove button
          activeButtons[i].remove();
          // add new button
          matrix.set(players[player].getColor(), addRandomButton(player), HIGH);
        }
      }
      return leastRemainingTime;
    }
};

#endif