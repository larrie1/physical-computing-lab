#include <Game.h>
#include <WhackAMole.h>
#include <Remember.h>
#include <Arduino.h>
#include <Utils.h>

Game *games[GAMES];
int gameIndex = 0;

void setup() {
  // add games
  games[0] = new WhackAMole(GameMode::SINGLEPLAYER);
  games[1] = new WhackAMole(GameMode::MULTIPLAYER);
  games[2] = new Remember();

  // Start Button
  pinMode(START_BUTTON_PIN, INPUT);
  digitalWrite(START_BUTTON_PIN, LOW);

  // Mode Button
  pinMode(MODE_BUTTON_PIN, INPUT);
  digitalWrite(MODE_BUTTON_PIN, LOW);

  // Button initialization
  pinMode(BUTTON_LOAD_PIN, OUTPUT);
  pinMode(BUTTON_CLOCK_ENABLE_PIN, OUTPUT);
  pinMode(BUTTON_CLOCK_PIN, OUTPUT);
  pinMode(BUTTON_DATA_PIN, INPUT);
 
  // Red LEDs initialization
  pinMode(RED_LATCH_PIN, OUTPUT);
  pinMode(RED_CLOCK_PIN, OUTPUT);
  pinMode(RED_DATA_PIN, OUTPUT);

  // Green LEDs initialization
  pinMode(GREEN_LATCH_PIN, OUTPUT);
  pinMode(GREEN_CLOCK_PIN, OUTPUT);
  pinMode(GREEN_DATA_PIN, OUTPUT);

  // Blue LEDs initialization
  pinMode(BLUE_LATCH_PIN, OUTPUT);
  pinMode(BLUE_CLOCK_PIN, OUTPUT);
  pinMode(BLUE_DATA_PIN, OUTPUT);

  // Buttons
  //initRegister(BUTTON_CLOCK_PIN, BUTTON_LATCH_PIN, BUTTON_DATA_PIN);

  // Red LEDs
  //initRegister(RED_CLOCK_PIN, RED_LATCH_PIN, RED_DATA_PIN);

  // Green LEDs
  //initRegister(GREEN_CLOCK_PIN, GREEN_LATCH_PIN, GREEN_DATA_PIN);

  // Blue LEDs
  //initRegister(BLUE_CLOCK_PIN,  BLUE_LATCH_PIN, BLUE_DATA_PIN);
}

void loop() {
  // Mode Selection
  if (digitalRead(MODE_BUTTON_PIN) == HIGH && !games[gameIndex]->isActive()) {
    gameIndex = ((gameIndex + 2) % GAMES) - 1; // check if gameIndex + 1 is within games count (it's + 2 and - 1 because of index 0)
  }

  // Start/Pause Game
  if (digitalRead(START_BUTTON_PIN) == HIGH) {
    games[gameIndex]->start();
  } else {
    games[gameIndex]->pause();
  }
}
