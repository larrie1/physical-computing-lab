/*
  Remember.h - Library for handling the game Remember.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Remember_h
#define Remember_h

#include <Game.h>
#include <Stopwatch.h>
#include <Utils.h>

#define MINIMUM_PATTERN_SIZE 3
#define MAXIMUM_PATTERN_SIZE 50

enum class RememberState {
    SHOWING,
    REMEMBER
};

class Remember : public Game {
    public:
        void start() override;

    private:
        RememberState state = RememberState::SHOWING;
        int patternSize = MINIMUM_PATTERN_SIZE;
        int pattern[MAXIMUM_PATTERN_SIZE];
        int rememberIndex = 0;
        void reset() override;
        void showPattern();
};

#endif