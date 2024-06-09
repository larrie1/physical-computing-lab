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
#include <Button.hpp>

class Game {
  public:
    Game(int level, GameMode mode) : level(level), mode(mode) {}

    bool isActive() { return isCurrentlyActive;};

    virtual void loop() {
        if (!isCurrentlyActive) {
            setup();
        }

        // update button list 
        update();

        // write current state to matrix and update players
        for (int i = 0; i < MAX_PLAYER && changed; i++) {
          matrix->write(players[i]->getColor(), changed * i);
          // just updated the led's
          if (i == MAX_PLAYER - 1) {
            changed = false;
          }
        }

        // end game
        // if (activePlayer.getTime() <= 0) {
        //     Serial.println("You ran out of time!");
        //     // TODO show score on display

        //     reset();

        //     // TODO show animation

        //     Serial.println("Back to menu ...");
        // }
    };

  protected:
    int level;
    GameMode mode;
    List<Player *> players;
    List<Button *> activeButtons;
    bool changed = false;

    virtual void setup() {
          // reset states
          matrix->setAllLow();

          // add players
          if (players.getSize() < MAX_PLAYER) {
            players.add(new Player(Color::RED));
            players.add(new Player(Color::GREEN));
          }

          // TODO show countdown
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
          // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I

          // activePlayer.startMove();
          // Serial.println("Player " + getPlayerColor(activePlayer.getColor()) + " starts!");

          isCurrentlyActive = true;
    };

    void pause() {
        // activePlayer.pauseTime();

        // TODO show pause icon
        // I 0 0 I
        // I 0 0 I
        // I 0 0 I
        // I 0 0 I
    }

    // Player getActivePlayer() { return activePlayer; };

    // void nextPlayer() {
    //     activePlayer.stopMove();
    //     if (activePlayer.getColor() == players[0].getColor()) {
    //         activePlayer = players[1];
    //     } else {
    //         activePlayer = players[0];
    //     }
    //     activePlayer.startMove();
    // };

    virtual void reset() {
        isCurrentlyActive = false;
        for (int i = 0; i < MAX_PLAYER; i++) {
            players[i]->reset();
        }
        activeButtons.clear();
        matrix->setAllLow();
        changed = false;
        isInMenu = true;
        Serial.println("Quitting the game ...");
    };

    void update() {
      List<int> toRemove;
      matrix->setAllLow();
      for (int i = 0; i < activeButtons.getSize(); i++) {
        double remainingTime = activeButtons[i]->getRemainingTime();
        if (remainingTime > 0) {
          // set led for player on
          matrix->set(players[activeButtons[i]->getPlayer()]->getColor(), activeButtons[i]->getIndex(), HIGH);
        } else {
          // add index 
          toRemove.add(i);
          // update score
          players[activeButtons[i]->getPlayer()]->updateScore(-1);
          // ran out of time for button
          changed = true;
          // reset the game
          reset();
        }
      }
      for (int i = 0; i < toRemove.getSize(); i++) {
        activeButtons.remove(i);
      }
    }

    void addRandomButton(int player, int size) {
      for (int i = 0; i < size; i++) {
          int index = rand() % (BUTTON_COUNT - 1);
          activeButtons.add(new Button(index, player, BUTTON_TIME * (debug * 10)));
          matrix->set(players[player]->getColor(), index, HIGH);
      }
      changed = true;
    }

  private:
    bool isCurrentlyActive = false;
    // Player activePlayer = players[0];
};

#endif