/*
  Game.hpp - Library for handling the game.
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
#include <Globals.hpp>

class Game {
  public:
    Game(int level, GameMode mode) : level(level), mode(mode) {}

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
        if (activePlayer.getTime() <= 0) {
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
    int level;
    List<int> activeButtons;
    GameMode mode;
    bool initialized = false;
    Player getActivePlayer() { return activePlayer; };

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

  private:
    bool isCurrentlyActive = false;
    Player players[MAX_PLAYER] = {Player(Color::RED), Player(Color::GREEN)};
    Player activePlayer = players[0];
};

#endif