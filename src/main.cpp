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

    // set pins and button array
    assignPins();

    if (debug) {
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
    } else {
        // initialize Lcd Display
        lcd.init();
        lcd.startScreen();
        delay(500);

        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(F("  Starting up ...   "));

        // // Print welcome message
        for (int i = 0; i < BUTTON_COUNT; i++) {
            setValueAt(i, static_cast<Color>(random(0, 2)));

            lcd.setCursor(i + 2, 3);
            lcd.print(F("#"));

            delay(200);
        }

        setAllLow();

        lcd.gameSelect();
        lcd.setCursor(0, gameIndex);
        lcd.blink();
    }

    // Set random seed
    randomSeed(analogRead(A0));
}

void loop() {
    if (games[gameIndex].game->isActive()) {
        // Keep game running
        games[gameIndex].game->loop();
    } else {
        // Read input
        if (debug && Serial.available() > 0) {
            input = Serial.read();
        }

        // Menu
        if (isInMenu) {
            Serial.println("Do you want to play " + games[gameIndex].name + "? (1) Start, (2) Next");
            // lcd.setCursor(0, gameIndex);
            isInMenu = false;
        }

        // Mode Selection
        if (input == buttonMap[1] || (!debug && buttons[0].pressed())) {
            gameIndex = (gameIndex + 1) % GAMES;
            // lcd.setCursor(0, gameIndex);
            isInMenu = true;
        }

        // Start Game
        if (input == buttonMap[0] || (!debug && buttons[1].pressed())) {
            Serial.println("Starting " + games[gameIndex].name + "...");
            games[gameIndex].game->setup(games[gameIndex].mode, gameIndex > 1 ? 1 : 0, gameIndex > 1 ? "Remember" : "Whack-A-Mole");
        }

        // reset input
        input = '%';
    }
}
