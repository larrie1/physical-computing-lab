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

  // Buttons
  initRegister(BUTTON_SHIFT_PIN, BUTTON_STORE_PIN, BUTTON_DATA_PIN);

  // Red LEDs
  initRegister(RED_SHIFT_PIN, RED_STORE_PIN, RED_DATA_PIN);

  // Green LEDs
  initRegister(GREEN_SHIFT_PIN, GREEN_STORE_PIN, GREEN_DATA_PIN);

  // Blue LEDs
  initRegister(BLUE_SHIFT_PIN,  BLUE_STORE_PIN, BLUE_DATA_PIN);
}

void loop() {
  // Mode Selection
  if (digitalRead(MODE_BUTTON_PIN) == HIGH && !games[gameIndex]->isActive()) {
    gameIndex++;
  }

  // Start/Pause Game
  if (digitalRead(START_BUTTON_PIN) == HIGH) {
    games[gameIndex]->start();
  } else {
    games[gameIndex]->pause();
  }
}
