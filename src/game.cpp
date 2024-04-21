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
    if (activePlayer.getColor() == Color::RED) {
        activePlayer = player2;
    } else {
        activePlayer = player1;
    }
}

void Game::nextGameMode() {
    switch (mode) {
    case GameMode::SINGLEPLAYER:
        mode = GameMode::MULTIPLAYER;
        break;
    case GameMode::MULTIPLAYER:
        mode = GameMode::SINGLEPLAYER;
        break;

    default:
        break;
    }
}

void Game::start() {
    if (!isCurrentlyActive) {
        isCurrentlyActive = true;
        // TODO show countdown or 
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I 
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I 
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I 
        // I 0 0 0 -> I I 0 0 -> I I I 0 -> I I I I 
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
    if (readRegisterAt(BUTTON_SHIFT_PIN, BUTTON_DATA_PIN, activeButton) == 1) {
        activePlayer.updateScore(1);
        if (mode == GameMode::MULTIPLAYER) {
            nextPlayer();
        }
        activeButton = randomButton();
    }

    // activate light for active button
    if (activePlayer.getColor() == Color::RED) {
        writeRegisterAt(RED_SHIFT_PIN, RED_STORE_PIN, RED_DATA_PIN, activeButton);
    } else if (activePlayer.getColor() == Color::GREEN) {
        writeRegisterAt(GREEN_SHIFT_PIN, GREEN_STORE_PIN, GREEN_DATA_PIN, activeButton);
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
