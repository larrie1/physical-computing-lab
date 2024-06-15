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

    virtual void setup(GameMode mode) {
          // reset states
          matrix.setAllLow();

          // add players
          for (uint8_t i = 0; i < static_cast<uint8_t>(mode); i++) {
              players[i] = Player(static_cast<Color>(i));
          }

          // TODO show countdown
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I

          isCurrentlyActive = true;
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
          for (uint8_t i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
              players[i].reset();
          }
          
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

    void pause() {
        // TODO show pause icon
        // I 0 0 I
        // I 0 0 I
        // I 0 0 I
        // I 0 0 I
    }

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

    void addRandomButton(int8_t player) {
      uint8_t buttonIndex = rand() % (BUTTON_COUNT - 1);
      int8_t arrayIndex = -1;
      uint8_t counter = 0;
      while (counter < BUTTON_COUNT) {
        // find empty button
        if (activeButtons[counter].getPlayer() == -1 && arrayIndex == -1) {
          arrayIndex = counter;
        } else if (activeButtons[counter].getIndex() == buttonIndex) {
          buttonIndex = rand() % (BUTTON_COUNT - 1);
          counter = 0;
        }
        counter++;
      }
      activeButtons[arrayIndex] = Button(buttonIndex, player, BUTTON_TIME * (debug * 10));
      changed = true;
    }

  private:
    bool isCurrentlyActive = false;
};

#endif