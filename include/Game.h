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
#include <ShiftIn.h>
#include <RgbMatrix.h>
#include <Arduino-List.hpp>

#define MAX_PLAYER 2
#define GAMES 3 // WhackAMole Singleplayer, WhackAMole Multiplayer, Remember
#define DIMENSION 4
#define REGISTER_COUNT 2
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
#define RED_LATCH_PIN 7
#define RED_DATA_PIN 8

// Green LEDs
#define GREEN_LATCH_PIN 10
#define GREEN_DATA_PIN 11

// Blue LEDs
#define BLUE_LATCH_PIN 13
#define BLUE_DATA_PIN 14

// Clock
#define CLOCK_PIN 6

enum class GameMode {
    SINGLEPLAYER,
    MULTIPLAYER
};

class Game {
  public:
    Game() : matrix(RgbMatrix<DIMENSION>), shift(ShiftIn<REGISTER_COUNT>) {}

    bool isActive();
    void begin():
    void pause();

    virtual void start();

  protected:
    RgbMatrix matrix;
    ShiftIn shift;
    Player getActivePlayer();

    void nextPlayer();
    void toggleLightAt(Color color, int index, int value);
    void setLedPattern(Color color, long pattern);

    virtual void reset();

  private:
    bool isCurrentlyActive = false;
    Player players[MAX_PLAYER] = {Player(Color::RED), Player(Color::GREEN)};
    Player activePlayer = players[0];
};

#endif