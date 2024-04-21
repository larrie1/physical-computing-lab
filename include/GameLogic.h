/*
  GameLogic.h - Library for handling the game logic.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef GameLogic_h
#define GameLogic_h

// Constans
#define LED_PIN 13

// Declarations
class GameLogic {
  public:
    GameLogic();
    void selectGameMode();
    void start();
};

#endif