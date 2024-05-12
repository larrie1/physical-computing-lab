/*
  Player.h - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Player_h
#define Player_h

#include <Stopwatch.h>
#include <RgbMatrix.h>

#define START_TIME 300000L // 5min in ms

class Player {
  public:
    Player(Color color) : color(Color::RED) {}

    inline Color getColor() {return color;}
    inline void updateScore(int value) {score += value;}
    inline void pauseTime() {}
    inline void stopMove() {watch.stop();}
    inline void startMove() {watch.start();}
    inline void reset() {
      score = 0;
      timeLeft = START_TIME;
      stopMove();
    }

    int getTime() {
      timeLeft -= watch.elapsedMilliseconds();
      if (timeLeft <= 0) {
          watch.stop();
          timeLeft = 0;
      }
      return timeLeft;
    }

  private:
    Color color;
    int score = 0;
    long timeLeft = START_TIME; 
    Stopwatch watch = Stopwatch();
};

#endif