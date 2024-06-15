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

    virtual void setup(GameMode mode, uint8_t highscoreAdress) {
          // reset states
          matrix.setAllLow();

          // add players
          for (uint8_t i = 0; i < static_cast<uint8_t>(mode); i++) {
              players[i] = Player(static_cast<Color>(i));
          }

          // start animation
          for (uint8_t i = 0; i < DIMENSION; i++) {
            matrix.set(Color::BLUE, i, HIGH);
            matrix.set(Color::BLUE, i + 4, HIGH);
            matrix.set(Color::BLUE, i + 8, HIGH);
            matrix.set(Color::BLUE, i + 12, HIGH);
            matrix.write(Color::BLUE, true);
            delay(1000);
          }

          isCurrentlyActive = true;
          this->highscoreAdress = highscoreAdress;
    }

    virtual void loop() {
        // update button list 
        update();

        // write current state to matrix and update players
        for (uint8_t i = 0; (i < sizeof(players) / sizeof(players[0])) && changed; i++) {
          // just updated the led's
          if (i == (sizeof(players) / sizeof(players[0])) - 1) {
            changed = false;
          }
          matrix.write(players[i].getColor(), !changed);
        }
    }

    void reset() {
      int bestPlayer = 0;
      // read current highscore
      int highscore = EEPROM.read(highscoreAdress);
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

      if (bestPlayer != -1) {
        Serial.println("Player " + getPlayerColor(players[bestPlayer].getColor()) + " won with a score of " + String(players[bestPlayer].getScore()) + "!");
      } else {
        Serial.println("It's a draw! Both players have a score of " + String(players[0].getScore()) + "!");
      }

      // handle new highscore
      if (players[bestPlayer].getScore() > highscore) {
        EEPROM.write(highscoreAdress, players[bestPlayer].getScore());
        Serial.print("New highscore for Game ");
        highscoreAdress == 0 ? Serial.print("WhackAMole") : Serial.print("Remember");
        Serial.println(": " + String(players[bestPlayer].getScore()));
      }

      // reset players
      for (uint8_t i = 0; i < sizeof(players) / sizeof(players[0]) && players[i].getScore() != 0; i++) {
        players[i].reset();
      }
          
      // reset buttons
      for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
          activeButtons[i].remove();
      }

      isCurrentlyActive = false;
      matrix.setAllLow();
      changed = false;
      isInMenu = true;
      Serial.println(F("Quitting the game ..."));
    }

  protected:
    Player players[MAX_PLAYER];
    Button activeButtons[BUTTON_COUNT];
    uint8_t level = 1;
    bool changed = false;

    void update() {
      matrix.setAllLow();
      for (uint8_t i = 0; activeButtons[i].getPlayer() != -1 && i < BUTTON_COUNT; i++) {
        double remainingTime = activeButtons[i].getRemainingTime();
        if (remainingTime > 0) {
          // set led for player on
          matrix.set(players[activeButtons[i].getPlayer()].getColor(), activeButtons[i].getIndex(), HIGH);
        } else {
          // update score
          players[activeButtons[i].getPlayer()].updateScore(-1);
          // Game lost
          if (players[activeButtons[i].getPlayer()].getScore() < 0) {
            Serial.println("Player " + getPlayerColor(players[activeButtons[i].getPlayer()].getColor()) + " lost!");
            reset();
            // since activeButtons get cleared within reset break the loop here
            break;
          }
          int8_t player = activeButtons[i].getPlayer();
          // remove button
          activeButtons[i].remove();
          // add new button
          addRandomButton(player);
        }
      }
    }

    void addRandomButton(int8_t player, long time = BUTTON_TIME) {
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
      activeButtons[arrayIndex] = Button(buttonIndex, player, time * (debug * 10));
      changed = true;
    }

  private:
    bool isCurrentlyActive = false;
    uint8_t highscoreAdress = 0;
};

#endif