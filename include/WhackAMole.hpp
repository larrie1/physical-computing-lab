/*
  WhackAMole.hpp - Library for handling the game WhackAMole.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef WhackAMole_hpp
#define WhackAMole_hpp

#include <Game.hpp>
#include <Arduino.h>

class WhackAMole : public Game {
    private:
        void loop() override { Game::loop(); }

        void setup(GameMode mode, uint8_t highscoreAdress) override {
          // call super method
          Game::setup(mode, highscoreAdress);

          for (uint8_t player = 0; player < static_cast<uint8_t>(mode); player++) {
            // add random button to each player
            Game::addRandomButton(player);
          }
        }

        void onPress(char input = '%') override {
          // iterate over all player when nothing changed yet
          for (uint8_t player = 0; player < MAX_PLAYER && !changed; player++) {
            // iterate over all active buttons
            for (uint8_t button = 0; Game::activeButtons[button].getPlayer() != -1 && button < BUTTON_COUNT; button++) {
              // Take button when it belongs to the correct player
                if (Game::activeButtons[button].getPlayer() == player) {
                  // take button if it is pressed
                  if (shift.pressed(Game::activeButtons[button].getIndex()) || input == buttonMap[Game::activeButtons[button].getIndex()]) {
                    // remove pressed button
                    Game::activeButtons[button].remove();
                    // update player's score
                    Game::players[player].updateScore(1);
                    // add new button
                    Game::addRandomButton(player);
                    // button got removed and a new one got added
                    changed = true;
                    // found button, break loop
                    break;
                  }
                }
              }
          }
        }
};

#endif