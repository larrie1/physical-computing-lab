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
    Player(Color color) : color(Color::RED) {}

    inline Color getColor() {return color;}

    inline void updateScore(int value) {
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
    int score = 0;
    double timeLeft = START_TIME; 
    Stopwatch watch = Stopwatch();
};

#endif