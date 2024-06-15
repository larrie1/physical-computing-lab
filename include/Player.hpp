/*
  Player.hpp - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Player_hpp
#define Player_hpp

#include <Arduino.h>
#include <Globals.hpp>

class Player {
  public:
    // Default constructor
    Player() : color(Color::RED) {}

    Player(Color color) : color(color) {}

    inline Color getColor() { return color; }
    inline int8_t getScore() { return score; }

    void updateScore(int8_t value) {
      score += value;
      Serial.println("Score of Player " + getPlayerColor(color) + ": " + String(score));
    }

    void reset() {
      Serial.println("Reset Player " + getPlayerColor(color));
      score = 0;
    }

  private:
    Color color;
    int8_t score = 0;
};

#endif