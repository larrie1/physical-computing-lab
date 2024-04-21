/*
  Player.h - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Player_h
#define Player_h

#include <Utils.h>

class Player {
  public:
    Player(Color color);
    Player();
    Color getColor();
    void updateScore(int value);
    int getTime();
    void reset();
    void pauseTime();

  private:
    int score;
    long time_left;
    Color color;
};

#endif