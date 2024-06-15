#include <Game.hpp>
#include <Remember.hpp>
#include <WhackAMole.hpp>
#include <Arduino.h>
#include <Globals.hpp>

// Game selection
struct GameStruct {
    Game *game;
    String name;
    GameMode mode;
};

// constants
static WhackAMole whackamole;
static Remember remember;
static uint8_t gameIndex = 0;
static char input = '%';

static GameStruct games[GAMES] = {
    { &whackamole, "WhackAMole Singleplayer", GameMode::SINGLEPLAYER },
    { &whackamole, "WhackAMole Multiplayer", GameMode::MULTIPLAYER },
    { &remember, "Remember Singleplayer", GameMode::SINGLEPLAYER },
    { &remember, "Remember Multiplayer", GameMode::MULTIPLAYER }
};

void setup() {
    Serial.begin(115200);

    if (!debug) {
        // Button initialization
        shift.begin(
            BUTTON_LOAD_PIN, 
            BUTTON_CLOCK_ENABLE_PIN, 
            BUTTON_DATA_PIN, 
            BUTTON_CLOCK_PIN
        );

        // Matrix LEDs initialization
        matrix.begin(
            RED_LATCH_PIN,
            RED_DATA_PIN,
            GREEN_LATCH_PIN,
            GREEN_DATA_PIN,
            BLUE_LATCH_PIN,
            BLUE_DATA_PIN,
            CLOCK_PIN
        );

        Serial.println();
        Serial.println(F("#################################################"));
        Serial.println(F("#           Matrix Game Console                 #"));
        Serial.println(F("#          Created by GridGurus                 #"));
        Serial.println(F("#                                               #"));      
        Serial.println(F("# Available Games:                              #"));
        Serial.println(F("#       - Whack-A-Mole Singleplayer             #"));
        Serial.println(F("#       - Whack-A-Mole Multiplayer              #"));
        Serial.println(F("#       - Remember Singleplayer                 #"));
        Serial.println(F("#       - Remember Multiplayer                  #"));
        Serial.println(F("#################################################"));
        Serial.println();
    } else {
        Serial.println();
        Serial.println(F("#################################################"));
        Serial.println(F("# Starting in debug mode                        #"));
        Serial.println(F("# The Matrix is emulated with follwing keys:    #"));
        Serial.println(F("#       1 2 3 4                                 #"));
        Serial.println(F("#       q w e r                                 #"));
        Serial.println(F("#       a s d f                                 #"));
        Serial.println(F("#       y x c v                                 #"));
        Serial.println(F("#################################################"));
        Serial.println();
    }
}

void loop() {
    // Read input
    if (debug && Serial.available() > 0) {
        input = Serial.read();
    } else if (debug) {
        input = '%';
    }

    if ((shift.pressed(0) && shift.pressed(1) && shift.pressed(2) && shift.pressed(3)) || (debug && input == 32)) {
        // Reset game
        games[gameIndex].game->reset();
    } else if (games[gameIndex].game->isActive()) {
        // Keep game running
        games[gameIndex].game->loop();
    } else {
        // Menu
        if (isInMenu) {
            Serial.println("Do you want to play " + games[gameIndex].name + "? (1) Start, (2) Next");
            isInMenu = false;
        }

        // Mode Selection
        if ((debug && input == buttonMap[1]) || shift.pressed(1)) {
            gameIndex = (gameIndex + 1) % GAMES;
            isInMenu = true;
        }

        // Start Game
        if ((debug && input == buttonMap[0]) || shift.pressed(0)) {
            Serial.println("Starting " + games[gameIndex].name + "...");
            games[gameIndex].game->setup(games[gameIndex].mode);
        }
    }
}
