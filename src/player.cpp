#include <Player.h>

Player::Player(Color color) {
    score = 0;
    this->color = color;
    time_left = 300000L; // 5min in ms
}

Player::Player() {
    score = 0;
    this->color = Color::RED;
    time_left = 300000L; // 5min in ms
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

void Player::pauseTime() {

}

void Player::reset() {
    score = 0;
    time_left = 300000;
}