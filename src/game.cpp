#include <Game.h>

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
    resetLeds();
}

void Game::setLedPattern(Color color, long pattern) {
    resetLeds();
    switch (color) {
        case Color::RED:
            writeToLed(RED_CLOCK_PIN, RED_LATCH_PIN, RED_DATA_PIN, pattern);
            break;
        case Color::GREEN:
            writeToLed(GREEN_CLOCK_PIN, GREEN_LATCH_PIN, GREEN_DATA_PIN, pattern);
            break;
        case Color::BLUE:
            writeToLed(GREEN_CLOCK_PIN, GREEN_LATCH_PIN, GREEN_DATA_PIN, pattern);
            break;

        default:
            resetLeds();
            break;
    }
} 

void Game::resetLeds() {
    resetLed(RED_CLOCK_PIN, RED_LATCH_PIN, RED_DATA_PIN);
    resetLed(GREEN_CLOCK_PIN, GREEN_LATCH_PIN, GREEN_DATA_PIN);
    resetLed(BLUE_CLOCK_PIN, BLUE_LATCH_PIN, BLUE_DATA_PIN);
}

void Game::toggleLightAt(Color color, int index, int value) {
    switch (color) {
        case Color::RED:
            writeRegisterAt(RED_CLOCK_PIN, RED_LATCH_PIN, RED_DATA_PIN, index, value);
            break;
        case Color::GREEN:
            writeRegisterAt(GREEN_CLOCK_PIN, GREEN_LATCH_PIN, GREEN_DATA_PIN, index, value);
            break;
        case Color::BLUE:
            writeRegisterAt(BLUE_CLOCK_PIN, BLUE_LATCH_PIN, BLUE_DATA_PIN, index, value);
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
