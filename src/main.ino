#include <Game.h>
#include <Arduino.h>
#include <Utils.h>

Game game = Game();

void setup() {
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
}

void loop() {
  // Mode Selection
  if (digitalRead(MODE_BUTTON_PIN) == HIGH && !game.isActive()) {
    game.nextGameMode();
  }

  // Start/Pause Game
  if (digitalRead(START_BUTTON_PIN) == HIGH) {
    game.start();
  } else {
    game.pause();
  }
}
