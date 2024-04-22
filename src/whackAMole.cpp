#include <WhackAMole.h>

WhackAMole::WhackAMole(GameMode mode) {
    this->mode = mode;
}

void WhackAMole::onButtonPress(bool correct) {
    // set score of active player and turn light off
    Game::getActivePlayer().updateScore(correct ? 1 : -1);
    Game::toggleLightAt(Game::getActivePlayer().getColor(), activeButton, LOW);

    // check whether it is the next player's turn
    if (mode == GameMode::MULTIPLAYER) {
        Game::nextPlayer();
    }

    // new random button and respective light on
    activeButton = randomButton();
    Game::toggleLightAt(Game::getActivePlayer().getColor(), activeButton, HIGH);
}

void WhackAMole::start() {
    // initial start
    if (!Game::isActive()) {
        Game::toggleLightAt(Game::getActivePlayer().getColor(), activeButton, HIGH);
    }

    // start player move and player time
    Game::start();

    // check if button is pressed
    if (readRegisterAt(BUTTON_SHIFT_PIN, BUTTON_DATA_PIN, activeButton) == HIGH) {
        onButtonPress(true);
    } else {
        for (int i = 0; i < BUTTON_COUNT && i != activeButton; i++) {
            // pressed wrong button
            if (readRegisterAt(BUTTON_SHIFT_PIN, BUTTON_DATA_PIN, i) == HIGH) {
                onButtonPress(false);
            }
        }
    }
}