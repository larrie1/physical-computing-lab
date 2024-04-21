#include <Player.h>

Player::Player() {
    score = 0;
    time_left = 300000; // 5min in ms
}

void Player::updateScore(int value) {
    score += value;
}

int Player::getTime() {
    return time_left;
}