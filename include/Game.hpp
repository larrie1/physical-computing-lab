/*
  Game.h - Library for handling the game.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Game_hpp
#define Game_hpp

#include <Player.hpp>
#include <Stopwatch.h>
#include <ShiftIn.h>
#include <RgbMatrix.h>
#include <Arduino.h>
#include <List.hpp>

#define MAX_PLAYER 2
#define GAMES 3 // WhackAMole Singleplayer, WhackAMole Multiplayer, Remember
#define DIMENSION 4
#define REGISTER_COUNT 2
#define BUTTON_COUNT 16

/** Constants **/
#define START_BUTTON_PIN  1
#define MODE_BUTTON_PIN 2
#define BUTTON_COUNT 16

// Buttons
#define BUTTON_LOAD_PIN 1
#define BUTTON_CLOCK_ENABLE_PIN 2
#define BUTTON_DATA_PIN 3
#define BUTTON_CLOCK_PIN 4

// Red LEDs
#define RED_LATCH_PIN 7
#define RED_DATA_PIN 8

// Green LEDs
#define GREEN_LATCH_PIN 10
#define GREEN_DATA_PIN 11

// Blue LEDs
#define BLUE_LATCH_PIN 13
#define BLUE_DATA_PIN 14

// Clock
#define CLOCK_PIN 6

enum class GameMode {
    SINGLEPLAYER,
    MULTIPLAYER
};

class Game {
  public:
    Game(RgbMatrix<DIMENSION> *matrix, ShiftIn<REGISTER_COUNT> *shift, bool debug) : matrix(matrix), shift(shift), debug(debug) {}

    bool isActive() { return isCurrentlyActive;};

    virtual void start() {
        if (!isCurrentlyActive) {
          isCurrentlyActive = true;
          // TODO show countdown
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          activePlayer.startMove();
          Serial.println("Player " + getPlayerColor(activePlayer.getColor()) + " starts!");
        }

        // end game
        if (*activePlayer.getTime() <= 0) {
            Serial.println("You ran out of time!");
            // TODO show score on display

            reset();

            // TODO show animation

            Serial.println("Back to menu ...");
        }
    };

    void pause() {
        activePlayer.pauseTime();

        // TODO show pause icon
        // I 0 0 I
        // I 0 0 I
        // I 0 0 I
        // I 0 0 I
    }

  protected:
    RgbMatrix<DIMENSION>* matrix;
    ShiftIn<REGISTER_COUNT>* shift;
    Player getActivePlayer() { return activePlayer; };
    bool debug;

    void nextPlayer() {
        activePlayer.stopMove();
        if (activePlayer.getColor() == players[0].getColor()) {
            activePlayer = players[1];
        } else {
            activePlayer = players[0];
        }
        activePlayer.startMove();
    };

    virtual void reset() {
        isCurrentlyActive = false;
        for (int i = 0; i < MAX_PLAYER; i++) {
            players[i].reset();
        }
        matrix->setAllLow();
    };

    String getPlayerColor(Color color) {
        switch (color) {
            case Color::RED:
                return "RED";
            case Color::GREEN:
                return "GREEN";
            case Color::BLUE:
                return "BLUE";
            default:
                return "UNKNOWN";
        }
    }

  private:
    bool isCurrentlyActive = false;
    Player players[MAX_PLAYER] = {Player(Color::RED), Player(Color::GREEN)};
    Player activePlayer = players[0];
};

#endif