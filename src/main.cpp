#include <Game.hpp>
#include <Remember.hpp>
#include <WhackAMole.hpp>
#include <List.hpp>
#include <Arduino.h>
#include <Globals.hpp>

// Register
RgbMatrix<DIMENSION> matrix = RgbMatrix<DIMENSION>();
ShiftIn<REGISTER_COUNT> shift = ShiftIn<REGISTER_COUNT>();

// constants
Game* games[GAMES];
WhackAMole whackamole_singleplayer = WhackAMole(GameMode::SINGLEPLAYER);
WhackAMole whackamole_multiplayer = WhackAMole(GameMode::MULTIPLAYER);
Remember remember_singleplayer = Remember(GameMode::SINGLEPLAYER); 
Remember remember_multiplayer = Remember(GameMode::MULTIPLAYER);
uint8_t gameIndex = 0;
bool isInMenu = true;

// debug 
const bool debug = true;
const char buttonMap[16] = {'1', '2', '3', '4', 'q', 'w', 'e', 'r', 'a', 's', 'd', 'f', 'y', 'x', 'c', 'v'};

String getGameName(uint8_t index) {
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

    // add games
    for (uint8_t game = 0; game < GAMES; game++) {
        switch (game) {
            case 0:
                games[game] = &whackamole_singleplayer;
                break;
            case 1:
                games[game] = &whackamole_multiplayer;
                break;
            case 2:
                games[game] = &remember_singleplayer;
                break;
            case 3:
                games[game] = &remember_multiplayer;
                break;
            
            default:
                break;
        }
    }
}

void loop() {
    if (isInMenu) {
        Serial.println("Do you want to play " + getGameName(gameIndex) + "? (1) Start, (2) Next");
        isInMenu = false;
    }

    // stop game
    if ((shift.pressed(0) && shift.pressed(1) && shift.pressed(2) && shift.pressed(3)) || debug && Serial.available() > 0 && Serial.read() == 32) {
        games[gameIndex]->reset();
    }

    if (games[gameIndex]->isActive()) {
        games[gameIndex]->loop();
    } else if (debug) {
        if (Serial.available() > 0) {
            char input = Serial.read();
            if (input == buttonMap[0]) {
                Serial.println("Starting " + getGameName(gameIndex) + "...");
                games[gameIndex]->loop();
            } else if (input == buttonMap[1]) {
                gameIndex = (gameIndex + 1) % GAMES;
                isInMenu = true;
            }
        }
    } else {
        // Mode Selection
        if ((shift.pressed(1))) {
            gameIndex = (gameIndex + 1) % GAMES;
            isInMenu = true;
        }

        // Start/Pause Game
        if (shift.pressed(0)) {
            Serial.println("Starting " + getGameName(gameIndex) + "...");
            games[gameIndex]->loop();
        }
    }
}
