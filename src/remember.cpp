#include <Remember.h>

void Remember::reset() {
    rememberIndex = 0;
    patternSize = MINIMUM_PATTERN_SIZE;
    state = RememberState::SHOWING;
}

void Remember::showPattern() {
    for (int i = 0; i < patternSize; i++) {
        pattern[i] = randomButton();
        writeRegisterAt(BLUE_CLOCK_PIN, BLUE_LATCH_PIN, BLUE_DATA_PIN, pattern[i], HIGH);
        delay(1000);
        writeRegisterAt(BLUE_CLOCK_PIN, BLUE_LATCH_PIN, BLUE_DATA_PIN, pattern[i], LOW);
    }
    state = RememberState::REMEMBER;
}

void Remember::start() {
    Game::start();

    if (patternSize >= MAXIMUM_PATTERN_SIZE) {
        reset();
    }

    if (state == RememberState::REMEMBER) {
         // correct button in order pressed
        if (readRegisterAt(BUTTON_CLOCK_PIN, BUTTON_DATA_PIN, pattern[rememberIndex]) == HIGH) {
            // completed the pattern, reset and show new pattern
            if (rememberIndex == patternSize) {
                Game::getActivePlayer().updateScore(1);
                state = RememberState::SHOWING;
                patternSize++;
                rememberIndex = 0;
                showPattern();
            } else { // correct but not yet completed
                rememberIndex++;
            }
        } else { // wrong button
            for (int i = 0; i < BUTTON_COUNT && i != pattern[rememberIndex]; i++) {
                // pressed wrong button
                if (readRegisterAt(BUTTON_CLOCK_PIN, BUTTON_DATA_PIN, i) == HIGH) {
                    // show red led indicating wrong button press
                    writeRegisterAt(RED_CLOCK_PIN, RED_LATCH_PIN, RED_DATA_PIN, i, HIGH);
                    writeRegisterAt(GREEN_CLOCK_PIN, GREEN_LATCH_PIN, GREEN_DATA_PIN, pattern[rememberIndex], HIGH);
                    Game::getActivePlayer().updateScore(-1);
                    delay(1000);
                    reset();
                }
            }
        }
    }
}