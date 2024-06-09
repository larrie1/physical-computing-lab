/*
  WhackAMole.hpp - Library for handling the game WhackAMole.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef WhackAMole_hpp
#define WhackAMole_hpp

#include <Game.hpp>
#include <ShiftIn.h>
#include <RgbMatrix.h>
#include <Arduino.h>
#include <List.hpp>
#include <Globals.hpp>

class WhackAMole : public Game {
    public:
        WhackAMole(GameMode mode) : Game(1, mode) {}

        void loop() override {
            // start player move and player time, write data every frame
            Game::loop();

            if (Game::isActive()) {
                // check if button is pressed
                if (!debug && shift->update()) {
                  onPress();
                } else {
                  // debug mode
                  if (Serial.available() > 0) {
                    onPress(Serial.read());
                  }
                }
            }
        }

    private:
        // void setupLevel() {
        //     int index = 0;
        //     matrix->setAllLow();
        //     for (int i = 0; i < level; i++) {
        //       // we do not want the same index in our list twice
        //       do {
        //         index = rand() % (BUTTON_COUNT - 1);
        //       } while (contains(index));

        //       activeButtons.add(index);
        //       matrix->set(Game::getActivePlayer().getColor(), index, HIGH);
        //     }
        //     matrix->write(Game::getActivePlayer().getColor(), true);
        // }

        void setup() override {
          // call super method
          Game::setup();

          if (mode == GameMode::SINGLEPLAYER) {
              Game::addRandomButton(PLAYER_1, level);
          } else {
              for (int player = 0; player < MAX_PLAYER; player++) {
                  Game::addRandomButton(player, level);
              }
          }
        }

        void onPress(char input = '%') {
          // iterate over all player when nothing changed yet
          for (int player = 0; player < MAX_PLAYER && !changed; player++) {
            // iterate over all active buttons
            for (int button = 0; button < Game::activeButtons.getSize(); button++) {
              // Take button when it belongs to the correct player
                if (Game::activeButtons[button]->getPlayer() == player) {
                  // take button if it is pressed
                  if (shift->pressed(Game::activeButtons[button]->getIndex()) || input == buttonMap[Game::activeButtons[button]->getIndex()]) {
                    // remove pressed button
                    Game::activeButtons.remove(button);
                    // update player's score
                    Game::players[player].updateScore(1);
                    // add new button
                    Game::addRandomButton(player, 1);
                    // button got removed and a new one got added
                    changed = true;
                    // found button, break loop
                    break;
                  }
                }
              }
          }
        }

        // bool contains(int target) {
        //     for (int i = 0; i < activeButtons.getSize(); i++) {
        //         if (activeButtons[i] == target) {
        //             return true; 
        //         }
        //     }
        //     return false; 
        // }

        // void onButtonPress(char input = 'none') {
        //     for (int i = 0; i < activeButtons.getSize(); i++) {
        //         if (shift->pressed(i) || input == buttonMap[activeButtons[i]]) {
        //           // remove pressed button
        //           activeButtons.remove(i);
        //           // turn led off
        //           matrix->set(Game::getActivePlayer().getColor(), activeButtons[i], LOW);
        //           // if it was the last button increase the score
        //           if (activeButtons.getSize() == 0) {
        //             Game::getActivePlayer().updateScore(1);
        //           }
        //           break;
        //         }
        //         // Pressed false Button 
        //         if (i == activeButtons.getSize()) {
        //           // set score of active player
        //           Game::getActivePlayer().updateScore(-1);
        //           // set all leds LOW
        //           matrix->setAllLow();
        //           // remove remaining buttons 
        //           activeButtons.clear();
        //         }
        //     }
        //     // write new data to matrix
        //     matrix->write(Game::getActivePlayer().getColor());

        //     if (activeButtons.getSize() == 0) {
        //       Serial.println("Next Level!");
        //       level++;
        //       setupLevel();

        //       // check whether it is the next player's turn
        //       if (mode == GameMode::MULTIPLAYER) {
        //           Game::nextPlayer();
        //       }
        //     }
        // }
};

#endif