/*
  WhackAMole.hpp - Library for handling the game WhackAMole.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef WhackAMole_hpp
#define WhackAMole_hpp

#include <Game.hpp>

class WhackAMole : public Game {
    private:
        void loop() override { Game::loop(); }

        void setup(GameMode mode, uint8_t highscoreAdress, String name) override {
          // call super method
          Game::setup(mode, highscoreAdress, name);

          for (uint8_t player = 0; player < static_cast<uint8_t>(mode); player++) {
            Serial.println("Player " + String(player) + " is active.");
            // add random button to each player
            Game::addRandomButton(player);
          }
        }

        void onPress(char input = '%') override {
          for (int i = 0; i < BUTTON_COUNT; i++) {
            int8_t player = buttons[i].getPlayer();
            if (buttons[i].pressed() && buttons[i].getValue() != Color::NONE) {
              Serial.println("Player " + String(player) + " pressed button " + String(i) + " with value " + String(static_cast<int>(buttons[i].getValue())) + ".");
              // remove pressed button
              buttons[i].setValue(Color::NONE);
              // update player's score
              Game::players[player].updateScore(1);
              // check if player reached next level, max 4 active Buttons
              if (Game::players[player].getScore() % 10 == 0 && Game::players[player].getScore() <= 40) {
                Game::players[player].updateLevel(1);
                Serial.println("Next Level");
                // add another button to player
                Game::addRandomButton(player);
              }
              // add new button
              Game::addRandomButton(player);
              // button got removed and a new one got added
              changed = true;
              // found button, break loop
              break;
            }
          }
        }
};

#endif