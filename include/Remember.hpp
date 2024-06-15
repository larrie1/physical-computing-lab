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
    public:

    //     void start() override {
    //         // start player move and player time
    //         Game::loop();

    //         if (state == RememberState::SHOWING) {
    //             // stop player watch
    //             Game::getActivePlayer().stopMove();
    //             // show button pattern
    //             showLevel();
    //             // start player watch
    //             Game::getActivePlayer().startMove();
    //         } 

    //         if (state == RememberState::REMEMBER) {
    //             // check if button is pressed
    //             if (shift->update()) {
    //                 onButtonPress();
    //             }
    //         }
    //     }

    // private:
    //     int wrongPressed = 0;
    //     RememberState state = RememberState::SHOWING;

    //     void showLevel() {
    //         for (int i = 0; i < level; i++) {
    //             int index = rand() % (BUTTON_COUNT - 1);
    //             activeButtons.add(index);

    //             matrix->set(Game::getActivePlayer().getColor(), index, HIGH);
    //             matrix->write(Game::getActivePlayer().getColor());
    //             delay(SHOW_TIME);
    //             matrix->setAllLow();
    //             matrix->write(Game::getActivePlayer().getColor());
    //         }
    //         // next state 
    //         state = RememberState::REMEMBER;
    //     }

    //     void onButtonPress() {
    //         if (shift->pressed(activeButtons[activeButtons.getSize() - 1])) {
    //             wrongPressed = 0;
    //             // turn led green
    //             matrix->flashWrite(Color::GREEN, SHOW_TIME, activeButtons[activeButtons.getSize() - 1]);

    //             activeButtons.removeLast();
    //         } else {
    //             wrongPressed++;
    //             Game::getActivePlayer().updateScore(-1);
    //             if (wrongPressed > WRONG_PRESSES_THRESHHOLD) {
    //                 Game::reset();
    //                 // TODO next player or next player won
    //             }
    //         }

    //         if (activeButtons.getSize() == 0) {
    //             // flash all leds green
    //             matrix->flashWrite(Color::GREEN, SHOW_TIME);

    //             level++;
    //             Game::getActivePlayer().updateScore(1);

    //             if (mode == GameMode::MULTIPLAYER) {
    //                 Game::nextPlayer();
    //             }

    //             state = RememberState::SHOWING;
    //         }
    //     }
};

#endif
