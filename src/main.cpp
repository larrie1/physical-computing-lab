#include <Game.hpp>
#include <Remember.hpp>
#include <WhackAMole.hpp>
#include <List.hpp>
#include <Arduino.h>
#include <Globals.hpp>

// Register
RgbMatrix<DIMENSION> *matrix = new RgbMatrix<DIMENSION>();
ShiftIn<REGISTER_COUNT> *shift = new ShiftIn<REGISTER_COUNT>();

// constants
List<Game*> games;
int gameIndex = 0;
bool debug = true;
char buttonMap[16] = { '1', '2', '3', '4', 'q', 'w', 'e', 'r', 'a', 's', 'd', 'f', 'y', 'x', 'c', 'v' };

String getGameName(int index) {
    switch (index) {
        case 0:
            return "WhackAMole Singleplayer";
        case 1:
            return "WhackAMole Multiplayer";
        case 2:
            return "Remember Singleplayer";
        case 3:
            return "Remember Multiplayer";
        default:
            return "Unknown";
    }
}

void setup() {
    Serial.begin(9600);

    if (!debug) {
        Serial.println();
        Serial.println("#################################################");
        Serial.println("#           Matrix Game Console                 #");
        Serial.println("#          Created by GridGurus                 #");
        Serial.println("#                                               #");      
        Serial.println("# Available Games:                              #");
        Serial.println("#       - Whack-A-Mole Singleplayer             #");
        Serial.println("#       - Whack-A-Mole Multiplayer              #");
        Serial.println("#       - Remember Singleplayer                 #");
        Serial.println("#       - Remember Multiplayer                  #");
        Serial.println("#################################################");
        Serial.println();

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
        Serial.println();
        Serial.println("#################################################");
        Serial.println("# Starting in debug mode                        #");
        Serial.println("# The Matrix is emulated with follwing keys:    #");
        Serial.println("#       1 2 3 4                                 #");
        Serial.println("#       q w e r                                 #");
        Serial.println("#       a s d f                                 #");
        Serial.println("#       y x c v                                 #");
        Serial.println("#################################################");
        Serial.println();
    }

    // add games
    games.add(new WhackAMole(GameMode::SINGLEPLAYER));
    games.add(new WhackAMole(GameMode::MULTIPLAYER));
    games.add(new Remember(GameMode::SINGLEPLAYER));
    games.add(new Remember(GameMode::MULTIPLAYER));

    Serial.println("Do you want to play " + getGameName(gameIndex) + "? (1) Start, (2) Next");
}

void loop() {
    if (games[0]->isActive() || games[1]->isActive() || games[2]->isActive()) {
        games[gameIndex]->start();
    } else if (debug) {
        if (Serial.available() > 0) {
            char input = Serial.read();
            if (input == buttonMap[0]) {
                Serial.println("Starting game " + getGameName(gameIndex) + "...");
                games[gameIndex]->start();
            }
            if (input == buttonMap[1]) {
                gameIndex = (gameIndex + 1) % GAMES;
                Serial.println("Do you want to play " + getGameName(gameIndex) + "? (1) Start, (2) Next");
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
