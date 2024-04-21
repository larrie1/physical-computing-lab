#include <Game.h>
#include <Arduino.h>

Game game = Game();

void setup() {
  // Start Button
  pinMode(START_BUTTON_PIN, INPUT);
  digitalWrite(START_BUTTON_PIN, LOW);

  // Mode Button
  pinMode(MODE_BUTTON_PIN, INPUT);
  digitalWrite(MODE_BUTTON_PIN, LOW);
}

void loop() {
  // Mode Selection
  if (digitalRead(MODE_BUTTON_PIN) == HIGH && !game.isCurrentlyActive) {
    game.nextGameMode();
  }

  // Start/Pause Game
  if (digitalRead(START_BUTTON_PIN) == HIGH) {
    game.start();
  } else {
    game.pause();
  }
}
