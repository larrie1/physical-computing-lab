/*
  Game.h - Library for handling the game.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef GameLogic_h
#define GameLogic_h

#include <Player.h>
#include <Utils.h>

/** Constans **/
#define START_BUTTON_PIN  1
#define MODE_BUTTON_PIN 2
#define BUTTON_COUNT 16

// Buttons
#define BUTTON_SHIFT_PIN 3
#define BUTTON_STORE_PIN 4
#define BUTTON_DATA_PIN 5

// Red LEDs
#define RED_SHIFT_PIN 6
#define RED_STORE_PIN 7
#define RED_DATA_PIN 8

// Green LEDs
#define GREEN_SHIFT_PIN 9
#define GREEN_STORE_PIN 10
#define GREEN_DATA_PIN 11

// Blue LEDs
#define BLUE_SHIFT_PIN 12
#define BLUE_STORE_PIN 13
#define BLUE_DATA_PIN 14


enum class GameMode {
    SINGLEPLAYER,
    MULTIPLAYER
};

// Declarations
class Game {
  public:
    Game();
    void nextGameMode();
    void start();
    void pause();
    bool isActive();
    GameMode getMode();
    void nextPlayer();

  private:
    GameMode mode;
    bool isCurrentlyActive;
    Player activePlayer;
    Player player1;
    Player player2;
    int activeButton;
};

#endif