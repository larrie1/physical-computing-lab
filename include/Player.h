/*
  Player.h - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Player_h
#define Player_h

#include <Utils.h>
#include <Stopwatch.h>

class Player {
  public:
    Player(Color color = Color::RED);
    Color getColor();
    void updateScore(int value);
    int getTime();
    void reset();
    void pauseTime();
    void stopMove();
    void startMove();

  private:
    Color color;
    int score = 0;
    long timeLeft = 300000L; // 5min in ms
    Stopwatch watch = Stopwatch();
};

#endif