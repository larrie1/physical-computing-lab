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

        void start() override {
            // start player move and player time
            Game::start();

            if (Game::isActive()) {
                // initial start
                if (!initialized) {
                    initialized = true;
                    setupLevel();
                }

                // check if button is pressed
                if (!debug && shift->update()) {
                  onButtonPress();
                } else {
                  // debug mode
                  if (Serial.available() > 0) {
                    onButtonPress(Serial.read());
                  }
                }
            }
        }

    private:
        void setupLevel() {
            int index = 0;
            matrix->setAllLow();
            for (int i = 0; i < level; i++) {
              // we do not want the same index in our list twice
              do {
                index = rand() % (BUTTON_COUNT - 1);
              } while (contains(index));

              activeButtons.add(index);
              matrix->set(Game::getActivePlayer().getColor(), index, HIGH);
            }
            matrix->write(Game::getActivePlayer().getColor(), true);
        }

        bool contains(int target) {
            for (int i = 0; i < activeButtons.getSize(); i++) {
                if (activeButtons[i] == target) {
                    return true; 
                }
            }
            return false; 
        }

        void onButtonPress(char input = 'none') {
            for (int i = 0; i < activeButtons.getSize(); i++) {
                if (shift->pressed(i) || input == buttonMap[activeButtons[i]]) {
                  // remove pressed button
                  activeButtons.remove(i);
                  // turn led off
                  matrix->set(Game::getActivePlayer().getColor(), activeButtons[i], LOW);
                  // if it was the last button increase the score
                  if (activeButtons.getSize() == 0) {
                    Game::getActivePlayer().updateScore(1);
                  }
                  break;
                }
                // Pressed false Button 
                if (i == activeButtons.getSize()) {
                  // set score of active player
                  Game::getActivePlayer().updateScore(-1);
                  // set all leds LOW
                  matrix->setAllLow();
                  // remove remaining buttons 
                  activeButtons.clear();
                }
            }
            // write new data to matrix
            matrix->write(Game::getActivePlayer().getColor());

            if (activeButtons.getSize() == 0) {
              Serial.println("Next Level!");
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