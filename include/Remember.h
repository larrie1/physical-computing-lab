/*
  Remember.h - Library for handling the game Remember.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Remember_h
#define Remember_h

#include <Game.h>

#define WRONG_PRESSES_THRESHHOLD 1
#define SHOW_TIME 1000

enum class RememberState {
    SHOWING,
    REMEMBER
};

class Remember : public Game {
    public:
        void start() override {
            // start player move and player time
            Game::start();

            if (state == RememberState::SHOWING) {
                // stop player watch
                Game::getActivePlayer().stopMove();
                // show button pattern
                showLevel();
                // start player watch
                Game::getActivePlayer().startMove();
            } 

            if (state == RememberState::REMEMBER) {
                // check if button is pressed
                if (Game::shift.update()) {
                    onButtonPress();
                }
            }
        }

    private:
        List<int> buttons;
        int level = 1;
        int wrongPressed = 0;
        RememberState state = RememberState::SHOWING;
        GameMode mode = GameMode::SINGLEPLAYER;

        void showLevel() {
            for (int i = 0; i < level; i++) {
                int index = rand() % (BUTTON_COUNT - 1);
                buttons.add(index);

                Game::matrix.set(Game::getActivePlayer().getColor(), index, HIGH);
                Game::matrix.write(Game::getActivePlayer().getColor());
                delay(SHOW_TIME);
                Game::matrix.setAllLow();
                Game::matrix.write(Game::getActivePlayer().getColor());
            }
            // next state 
            state = RememberState::REMEMBER;
        }

        void onButtonPress() {
            if (Game::shift.pressed(buttons[buttons.getSize() - 1])) {
                wrongPressed = 0;
                // turn led green
                Game::matrix.flashWrite(Color::GREEN, SHOW_TIME, buttons[buttons.getSize() - 1]);

                buttons.removeLast();
            } else {
                wrongPressed++;
                Game::getActivePlayer().updateScore(-1);
                if (wrongPressed > WRONG_PRESSES_THRESHHOLD) {
                    Game::reset();
                    // TODO next player or next player won
                }
            }

            if (buttons.getSize() == 0) {
                // flash all leds green
                Game::matrix.flashWrite(Color::GREEN, SHOW_TIME);

                level++;
                Game::getActivePlayer().updateScore(1);

                if (mode == GameMode::MULTIPLAYER) {
                    Game::nextPlayer();
                }

                state = RememberState::SHOWING;
            }
        }
};

#endif
