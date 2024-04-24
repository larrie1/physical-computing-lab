/*
  Game.h - Library for handling the game.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Game_h
#define Game_h

#include <Player.h>
#include <Utils.h>
#include <Stopwatch.h>

#define MAX_PLAYER 2
#define GAMES 3 // WhackAMole Singleplayer, WhackAMole Multiplayer, Remember
#define BUTTON_COUNT 16

/** Constants **/
#define START_BUTTON_PIN  1
#define MODE_BUTTON_PIN 2
#define BUTTON_COUNT 16

// Buttons
#define BUTTON_LOAD_PIN 1
#define BUTTON_CLOCK_ENABLE_PIN 2
#define BUTTON_DATA_PIN 3
#define BUTTON_CLOCK_PIN 4

// Red LEDs
#define RED_CLOCK_PIN 6
#define RED_LATCH_PIN 7
#define RED_DATA_PIN 8

// Green LEDs
#define GREEN_CLOCK_PIN 9
#define GREEN_LATCH_PIN 10
#define GREEN_DATA_PIN 11

// Blue LEDs
#define BLUE_CLOCK_PIN 12
#define BLUE_LATCH_PIN 13
#define BLUE_DATA_PIN 14

enum class GameMode {
    SINGLEPLAYER,
    MULTIPLAYER
};

// Declarations
class Game {
  public:
    bool isActive();
    virtual void start();
    void pause();

  protected:
    Player getActivePlayer();
    void nextPlayer();
    void toggleLightAt(Color color, int index, int value);
    virtual void reset();
    void setLedPattern(Color color, long pattern);
    void resetLeds();

  private:
    bool isCurrentlyActive = false;
    Player players[MAX_PLAYER] = {Player(Color::RED), Player(Color::GREEN)};
    Player activePlayer = players[0];
};

#endif