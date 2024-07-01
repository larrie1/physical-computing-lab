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
            // add random button to each player
            Game::addRandomButton(player);
          }
        }

        void onPress(char input = '%') override {
          for (Button button : buttons) {
            int8_t player = button.getPlayer();
            if (button.pressed()) {
              // remove pressed button
              button.setValue(Color::NONE);
              // update player's score
              Game::players[player].updateScore(1);
              // check if player reached next level
              if (Game::players[player].getScore() % 10 == 0) {
                level++;
                // add another button to each player
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