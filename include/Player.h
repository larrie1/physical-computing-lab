/*
  Player.h - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Player_h
#define Player_h

class Player {
  public:
    Player();
    void updateScore(int value);
    int getTime();

  private:
    int score;
    int time_left;
};

#endif