#include <Game.h>

Game::Game() {
    isCurrentlyActive = false;
    player1 = Player(Color::RED);
    player2 = Player(Color::GREEN);
    activePlayer = player1;
    mode = GameMode::SINGLEPLAYER;
    activeButton = randomButton();
}

bool Game::isActive() {
    return isCurrentlyActive;
}

GameMode Game::getMode() {
    return mode;
}

void Game::nextPlayer() {
    if (activePlayer.getColor() == player1.getColor()) {
        activePlayer = player2;
    } else {
        activePlayer = player1;
    }
}

void Game::nextGameMode() {
    if (mode == GameMode::SINGLEPLAYER) {
        mode = GameMode::MULTIPLAYER;
    } else if (mode == GameMode::MULTIPLAYER) {
        mode = GameMode::SINGLEPLAYER;
    }
}

void Game::start() {
    if (!isCurrentlyActive) {
        isCurrentlyActive = true;
        // TODO show countdown
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I 
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I 
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I 
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I
        toggleLightAt(activePlayer.getColor(), activeButton);
    }

    // end game
    if (activePlayer.getTime() == 0) {
        isCurrentlyActive = false;
        player1.reset();
        player2.reset();
        activePlayer = player1;

        // TODO show animation
    }

    // check if button is pressed
    if (readRegisterAt(BUTTON_SHIFT_PIN, BUTTON_DATA_PIN, activeButton) == HIGH) {
        activePlayer.updateScore(1);
        toggleLightAt(activePlayer.getColor(), activeButton);
        if (mode == GameMode::MULTIPLAYER) {
            nextPlayer();
        }
        activeButton = randomButton();
    } else {
        for (int i = 0; i < BUTTON_COUNT && i != activeButton; i++) {
            // pressed wrong button
            if (readRegisterAt(BUTTON_SHIFT_PIN, BUTTON_DATA_PIN, i) == HIGH) {
                activePlayer.updateScore(-1);
                toggleLightAt(activePlayer.getColor(), activeButton);
                if (mode == GameMode::MULTIPLAYER) {
                    nextPlayer();
                }
                activeButton = randomButton();
            }
        }
    }
}

void Game::pause() {
    activePlayer.pauseTime();

    // TODO show pause icon
    // 0 0 0 0
    // I 0 0 I
    // I 0 0 I
    // 0 0 0 0
}
