#include <Game.hpp>
#include <Remember.hpp>
#include <WhackAMole.hpp>
#include <List.hpp>
#include <Arduino.h>

RgbMatrix<DIMENSION>* matrix;
ShiftIn<REGISTER_COUNT>* shift;
List<Game*> games;
int gameIndex = 0;
bool debug = true;

String getGameName(int index) {
    switch (index) {
        case 0:
            return "WhackAMole Singleplayer";
        case 1:
            return "WhackAMole Multiplayer";
        case 2:
            return "Remember";
        default:
            return "Unknown";
    }
}

void setup() {
    Serial.begin(9600);

    if (!debug) {
        // Button initialization
        shift->begin(
            BUTTON_LOAD_PIN, 
            BUTTON_CLOCK_ENABLE_PIN, 
            BUTTON_DATA_PIN, 
            BUTTON_CLOCK_PIN
        );

        // Matrix LEDs initialization
        matrix->begin(
            RED_LATCH_PIN,
            RED_DATA_PIN,
            GREEN_LATCH_PIN,
            GREEN_DATA_PIN,
            BLUE_LATCH_PIN,
            BLUE_DATA_PIN,
            CLOCK_PIN
        );
    } else {
        Serial.println("Starting in debug mode");
    }

    Game* game1 = new WhackAMole(GameMode::SINGLEPLAYER, matrix, shift, debug);
    Game* game2 = new WhackAMole(GameMode::MULTIPLAYER, matrix, shift, debug);
    Game* game3 = new Remember(matrix, shift, debug);

    // add games
    games.add(game1);
    games.add(game2);
    games.add(game3);

    Serial.println("Do you want to play " + getGameName(gameIndex) + "? (s) Start, (n) Next");
}

void loop() {
    if (games[0]->isActive() || games[1]->isActive() || games[2]->isActive()) {
        games[gameIndex]->start();
    } else if (debug) {
        if (Serial.available() > 0) {
            char input = Serial.read();
            if (input == 's') {
                Serial.println("Starting game " + getGameName(gameIndex) + "...");
                games[gameIndex]->start();
            }
            if (input == 'n') {
                gameIndex = (gameIndex + 1) % GAMES;
                Serial.println("Do you want to play " + getGameName(gameIndex) + "? (s) Start, (n) Next");
            }
        }
        delay(1000);
    } else {
        if (!games[gameIndex]->isActive()) {
            // Mode Selection
            if ((shift->pressed(1))) {
                gameIndex = (gameIndex + 1) % GAMES;
            }

            // Start/Pause Game
            if (shift->pressed(0)) {
                games[gameIndex]->start();
            }
        } else {
            // handle pause / stop
        }
    }
}
