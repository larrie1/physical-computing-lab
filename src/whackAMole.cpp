#include <WhackAMole.h>

WhackAMole::WhackAMole(GameMode mode, int activeButtonsSize) {
    this->mode = mode;
    this->activeButtonsSize = activeButtonsSize;
    this->activeButtons = randomBitsList(activeButtonsSize);
}

void WhackAMole::onButtonPress(bool correct) {
    // set score of active player and turn light off
    Game::getActivePlayer().updateScore(correct ? 1 : -1);

    // check whether it is the next player's turn
    if (mode == GameMode::MULTIPLAYER) {
        Game::nextPlayer();
    }

    // new random button and respective light on
    activeButtons = randomBitsList(activeButtonsSize);
}

void WhackAMole::isButtonPressed(long activeButton) {
    if (readButtons(BUTTON_LOAD_PIN, BUTTON_CLOCK_PIN, BUTTON_CLOCK_ENABLE_PIN, BUTTON_DATA_PIN) == activeButton) {
        onButtonPress(true);
    } else {
        for (int i = 0; i < BUTTON_COUNT; i++) {
            // pressed wrong button
            if ((activeButton >> i & 1) == HIGH) {
                onButtonPress(false);
            }
        }
    }
}

void WhackAMole::setActive() {
    for (int i = 0; i < activeButtonsSize; i++) {
        Game::setLedPattern(Game::getActivePlayer().getColor(), activeButtons[i]);
    }
}

void WhackAMole::start() {
    // initial start
    if (!Game::isActive()) {
        setActive();
    }

    // start player move and player time
    Game::start();

    // check if button is pressed
    for (int i = 0; i < activeButtonsSize; i++) {
        isButtonPressed(activeButtons[i]);
    }
}