#include <Game.h>

Game::Game() {
    // Button initialization
    shift.begin(
        BUTTON_LOAD_PIN, 
        BUTTON_CLOCK_ENABLE_PIN, 
        BUTTON_DATA_PIN, 
        BUTTON_CLOCK_PIN
    );
 
    // Matrix LEDs initialization
    matrix.begin(
        RED_LATCH_PIN,
        RED_DATA_PIN,
        GREEN_LATCH_PIN,
        GREEN_DATA_PIN,
        BLUE_LATCH_PIN,
        BLUE_DATA_PIN,
        CLOCK_PIN
    );
}

bool Game::isActive() {
    return isCurrentlyActive;
}

Player Game::getActivePlayer() {
    return activePlayer;
}

void Game::nextPlayer() {
    activePlayer.stopMove();
    if (activePlayer.getColor() == players[0].getColor()) {
        activePlayer = players[1];
    } else {
        activePlayer = players[0];
    }
    activePlayer.startMove();
}

void Game::reset() {
    isCurrentlyActive = false;
    for (int i = 0; i < MAX_PLAYER; i++) {
        players[i].reset();
    }
    matrix.setAllLow();
}

void Game::start() {
    if (!isCurrentlyActive) {
        isCurrentlyActive = true;
        // TODO show countdown
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
        activePlayer.startMove();
    }

    // end game
    if (activePlayer.getTime() <= 0) {
        // TODO show score on display

        reset();

        // TODO show animation
    }    
}

void Game::pause() {
    activePlayer.pauseTime();

    // TODO show pause icon
    // I 0 0 I
    // I 0 0 I
    // I 0 0 I
    // I 0 0 I
}
