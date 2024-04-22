/*
  Utils.h - Library for handling the gamemode WhackAMole.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef WhackAMole_h
#define WhackAMole_h

#include <Game.h>

class WhackAMole : public Game {
    public:
        WhackAMole(GameMode mode = GameMode::SINGLEPLAYER);
        void start() override;
    
    private:
        int activeButton = randomButton();
        GameMode mode;
        void onButtonPress(bool correct);
};

#endif