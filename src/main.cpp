#include <Game.h>
#include <WhackAMole.h>
#include <Remember.h>
#include <Arduino.h>
#include <List.hpp>

List<Game> games;
int gameIndex = 0;

void setup() {
    // add games
    games.add(WhackAMole(GameMode::SINGLEPLAYER));
    games.add(WhackAMole(GameMode::MULTIPLAYER));
    games.add(Remember());

    // Start Button
    pinMode(START_BUTTON_PIN, INPUT);
    digitalWrite(START_BUTTON_PIN, LOW);

    // Mode Button
    pinMode(MODE_BUTTON_PIN, INPUT);
    digitalWrite(MODE_BUTTON_PIN, LOW);
}

void loop() {
  // Mode Selection
  if (digitalRead(MODE_BUTTON_PIN) == HIGH && !games[gameIndex].isActive()) {
    gameIndex = ((gameIndex + 2) % GAMES) - 1; // check if gameIndex + 1 is within games count (it's + 2 and - 1 because of index 0)
  }

  // Start/Pause Game
  if (digitalRead(START_BUTTON_PIN) == HIGH) {
    games[gameIndex].start();
  } else {
    games[gameIndex].pause();
  }
}
