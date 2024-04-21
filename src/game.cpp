#include <Game.h>
#include <Utils.h>

Player player1 = Player(Color::RED);
Player player2 = Player(Color::GREEN);

Game::Game() {
    isCurrentlyActive = false;
    activePlayer = player1;
    mode = GameMode::SINGLEPLAYER;
    activeButton = random();
}

bool Game::isActive() {
    return isCurrentlyActive;
}

GameMode Game::getMode() {
    return mode;
}

void Game::nextPlayer() {
    if (activePlayer == player1) {
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
        isCurrentlyActive = true
        // TODO show countdown
    }

    // check if button is pressed
    if (readRegisterAt(BUTTON_SHIFT_PIN, BUTTON_DATA_PIN, activeButton) == 1) {
        activePlayer.updateScore(1);
        if (mode == GameMode::MULTIPLAYER) {
            nextPlayer();
        }
        activeButton = random();
    }

    // activate light for active button
    if (activePlayer.getColor() == Color::RED) {
        writeRegisterAt(RED_SHIFT_PIN, RED_STORE_PIN, RED_DATA_PIN, activeButton);
    } else if (activePlayer.getColor() == Color::GREEN) {
        writeRegisterAt(GREEN_SHIFT_PIN, GREEN_STORE_PIN, GREEN_DATA_PIN, activeButton);
    }
}

// TODO stop timer and show it on the board
void Game::pause() {

}
