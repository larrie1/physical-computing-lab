/*
  WhackAMole.h - Library for handling the game WhackAMole.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef WhackAMole_h
#define WhackAMole_h

#include <Game.h>

class WhackAMole : public Game {
    public:
        WhackAMole(GameMode mode) : mode(GameMode::SINGLEPLAYER), level(1) {}

        void start() override {
            // initial start
            if (!Game::isActive()) {
              setupLevel();
            }

            // start player move and player time
            Game::start();

            // check if button is pressed
            if (Game::shift.update()) {
                onButtonPress()
            }
        }
    
    private:
        int level;
        List<int> activeButtons;
        GameMode mode;

        void setupLevel() {
            int index = 0;

            for (int i = 0; i < level; i++) {
              // we do not want the same index in our list twice
              do {
                index = rand() % (BUTTON_COUNT - 1);
              } while (contains(index));

              activeButtons.add(index);
              Game::matrix.set(Game::getActivePlayer().getColor(), index, HIGH);
            }

            Game::matrix.write(Game::getActivePlayer().getColor());
        }

        bool contains(int target) {
            for (int i = 0; i < activeButtons.getSize(); i++) {
                if (activeButtons[i] == target) {
                    return true; 
                }
            }
            return false; 
        }

        void onButtonPress() {
            for (int i = 0; i < BUTTON_COUNT; i++) {
                if (Game::shift.pressed(i)) {
                    if (contains(i)) {
                        // remove pressed button
                        activeButtons.remove(i);
                        // turn led off
                        Game::matrix.set(Game::getActivePlayer().getColor(), i, LOW);
                        // if it was the last button increase the score
                        if (activeButtons.getSize() == 0) {
                          Game::getActivePlayer().updateScore(1);
                        }
                    } else {
                      // set score of active player
                      Game::getActivePlayer().updateScore(-1);
                      // set all leds LOW
                      Game::matrix.setAllLow();
                      // remove remaining buttons 
                      activeButtons.clear();
                    }
                }
            }
            // write new data to matrix
            Game::matrix.write(Game::getActivePlayer().getColor(), false);

            if (activeButtons.getSize() == 0) {
              level++;
              setupLevel();

              // check whether it is the next player's turn
              if (mode == GameMode::MULTIPLAYER) {
                  Game::nextPlayer();
              }
            }
        }
};

#endif