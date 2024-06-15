/*
  Remember.hpp - Library for handling the game Remember.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Remember_hpp
#define Remember_hpp

#include <Game.hpp>
#include <ShiftIn.h>
#include <RgbMatrix.h>
#include <Globals.hpp>

enum class RememberState {
    SHOWING,
    REMEMBER
};

class Remember : public Game {
    private:
        RememberState state = RememberState::SHOWING;
        GameMode mode = GameMode::UNKNOWN;
        uint8_t player = 0;
        int8_t sequence[50];
        uint8_t index = 0;

        void setup(GameMode mode, uint8_t highscoreAdress) override {
          // call super method
          Game::setup(mode, highscoreAdress);
          this->mode = mode;
          index = 0;
          player = 0;
          state = RememberState::SHOWING;

          // set all sequence values to -1
          for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
              sequence[i] = -1;
          }
        }

        void loop() override {
            if (state == RememberState::SHOWING) {
                show();
            } else {
                // write data and check inputs
                Game::loop();
            }
        }

        void show() {
            for (int i = 0; i < level; i++) {
                uint8_t index = random(0, BUTTON_COUNT);
                // show button for 1 second
                matrix.set(Color::BLUE, index, HIGH);
                matrix.write(Color::BLUE, true);
                // add button to sequence
                sequence[i] = index;
                delay(1000);
                // remove button after 1 second
                matrix.setAllLow();
            }
            matrix.writeAll();
            changed = false;
            state = RememberState::REMEMBER;
        }

        void onPress(char input = '%') override {
            bool correct = false;
            // iterate over all active buttons
            for (uint8_t button = 0; button < BUTTON_COUNT; button++) {
                // take button if it is pressed
                if (shift.pressed(button) || input == buttonMap[button]) {
                    // check if button is the correct in sequence
                    if (button == sequence[index]) {
                        correct = true;
                        matrix.set(Color::GREEN, button, HIGH);
                        // remove pressed button
                        sequence[index] = -1;
                        index++;
                    } else {
                        Game::players[player].updateScore(-1);
                        if (Game::players[player].getScore() < 0) {
                            Serial.println("Player " + getPlayerColor(players[player].getColor()) + " lost!");
                            Game::reset();
                        }
                        matrix.set(Color::RED, button, HIGH);
                    }
                    matrix.write(correct ? Color::GREEN : Color::RED, false);
                    delay(500);
                    matrix.setAllLow();
                    break;
                }
            }

            // check if all buttons were pressed
            if (sequence[level - 1] == -1) {
                Game::players[player].updateScore(1);
                index = 0;
                state = RememberState::SHOWING;
                changed = true;
                // next player
                if (mode == GameMode::MULTIPLAYER) {
                    player = player == 0 ? 1 : 0;
                }
                // next level if all player did their move
                if (player == 0) {
                    level++;
                }
            }
        }
};

#endif
