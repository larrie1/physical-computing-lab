/*
  Player.h - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Player_h
#define Player_h

enum class Color {
  RED,
  GREEN
};

class Player {
  public:
    Player(Color color);
    Color getColor();
    void updateScore(int value);
    int getTime();
    void reset();

  private:
    int score;
    int time_left;
    Color color;
};

#endif