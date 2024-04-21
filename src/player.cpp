#include <Player.h>

Player::Player(Color color) {
    score = 0;
    color = color;
    time_left = 300000; // 5min in ms
}

Color Player::getColor() {
    return color;
}

void Player::updateScore(int value) {
    score += value;
}

int Player::getTime() {
    return time_left;
}

void Player::reset() {
    score = 0;
    time_left = 300000;
}