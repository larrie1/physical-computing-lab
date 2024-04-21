#include <Game.h>

Game::Game() {
    isCurrentlyActive = false;
    mode = 0;
    modes[0] = GameMode::SINGLEPLAYER;
    modes[1] = GameMode::MULTIPLAYER;
}

void Game::nextGameMode() {
    mode = ((mode + 2) % sizeof(modes)) - 1;
}

void Game::start() {

}

void Game::pause() {

}
