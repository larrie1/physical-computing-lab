/*
  Player.hpp - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Player_h
#define Player_h

#include <Stopwatch.h>
#include <RgbMatrix.h>
#include <Arduino.h>
#include <Globals.hpp>
#include <Button.hpp>
#include <List.hpp>

class Player {
  public:
    // Default constructor
    Player() : color(Color::RED) {}

    Player(Color color) : color(color) {}

    inline Color getColor() {return color;}
    inline int8_t getScore() {return score;}

    inline void updateScore(int8_t value) {
      score += value;
      Serial.println("Score of Player " + getPlayerColor(color) + ": " + String(score));
    }

    inline void pauseTime() {}

    inline void stopMove() {
      Serial.println("Player " + getPlayerColor(color) + " has " + String(timeLeft) + "ms left.");
      timeLeft = timeLeft - watch.elapsedMilliseconds();
      watch.stop();
    }
    
    inline void startMove() {watch.start();}

    inline void reset() {
      Serial.println("Reset Player " + getPlayerColor(color));
      score = 0;
      timeLeft = START_TIME;
      stopMove();
    }

    double getTime() {
      double elapsed = timeLeft - watch.elapsedMilliseconds();
      return elapsed;
    }

  private:
    Color color;
    int8_t score = 0;
    double timeLeft = START_TIME; 
    Stopwatch watch = Stopwatch();
};

#endif