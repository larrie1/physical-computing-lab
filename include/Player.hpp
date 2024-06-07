/*
  Player.h - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Player_h
#define Player_h

#include <Stopwatch.h>
#include <RgbMatrix.h>

#define START_TIME 300000 // 5min in ms

class Player {
  public:
    Player(Color color) : color(Color::RED) {}

    inline Color getColor() {return color;}
    inline void updateScore(int value) {score += value;}
    inline void pauseTime() {}
    inline void stopMove() {
      Serial.println("You have " + String(timeLeft) + "ms left.");
      timeLeft = timeLeft - watch.elapsedMilliseconds();
      watch.stop();
    }
    inline void startMove() {watch.start();}
    inline void reset() {
      score = 0;
      timeLeft = START_TIME;
      stopMove();
    }

    double* getTime() {
      double elapsed = timeLeft - watch.elapsedMilliseconds();
      return &elapsed;
    }

  private:
    Color color;
    int score = 0;
    double timeLeft = START_TIME; 
    Stopwatch watch = Stopwatch();
};

#endif