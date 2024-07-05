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

    bool isActive = false;

    inline Color getColor() { return color; }
    inline int8_t getScore() { return score; }
    inline int8_t getLives() { return lives; }
    inline int8_t getLevel() { return level; }
    inline void updateLevel(int8_t value) { level += value; }

    void updateScore(int8_t value) {
      if (value == -1) {
        lives--;
      } 

      if (value == -1 && score > 0 || value > 0) {
        score += value;
      }
      
      Serial.println("Score of Player " + getPlayerColor(color) + ": " + String(score));
    }

    void reset() {
      Serial.println("Reset Player " + getPlayerColor(color));
      score = 0;
      lives = 3;
      level = 1;
      isActive = false;
    }

  private:
    Color color;
    int8_t level = 1;
    int8_t lives = 3;
    int8_t score = 0;
};

#endif