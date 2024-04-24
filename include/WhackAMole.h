/*
  WhackAMole.h - Library for handling the game WhackAMole.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef WhackAMole_h
#define WhackAMole_h

#include <Game.h>

class WhackAMole : public Game {
    public:
        WhackAMole(GameMode mode = GameMode::SINGLEPLAYER, int activeButtonsSize = 1);
        void start() override;
    
    private:
        int activeButtonsSize;
        long* activeButtons;
        GameMode mode;
        void onButtonPress(bool correct);
        void isButtonPressed(long activeButton);
        void setActive();
};

#endif