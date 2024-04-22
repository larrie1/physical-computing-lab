#include <Game.h>

bool Game::isActive() {
    return isCurrentlyActive;
}

Player Game::getActivePlayer() {
    return activePlayer;
}

void Game::nextPlayer() {
    if (activePlayer.getColor() == players[0].getColor()) {
        activePlayer = players[1];
    } else {
        activePlayer = players[0];
    }
}

void Game::reset() {
    isCurrentlyActive = false;
    for (int i = 0; i < MAX_PLAYER; i++) {
        players[i].reset();
    }
}

void Game::toggleLightAt(Color color, int index, int value) {
    switch (color) {
        case Color::RED:
            writeRegisterAt(RED_SHIFT_PIN, RED_STORE_PIN, RED_DATA_PIN, index, value);
            break;
        case Color::GREEN:
            writeRegisterAt(GREEN_SHIFT_PIN, GREEN_STORE_PIN, GREEN_DATA_PIN, index, value);
            break;
        case Color::BLUE:
            writeRegisterAt(BLUE_SHIFT_PIN, BLUE_STORE_PIN, BLUE_DATA_PIN, index, value);
            break;
        
        default:
            break;
    }
}

void Game::start() {
    if (!isCurrentlyActive) {
        isCurrentlyActive = true;
        activePlayer.startMove();
        // TODO show countdown
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
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
