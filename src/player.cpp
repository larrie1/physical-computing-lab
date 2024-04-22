#include <Player.h>

Player::Player(Color color) {
    this->color = color;
}

Color Player::getColor() {
    return color;
}

void Player::stopMove() {
    watch.stop();
}

void Player::startMove() {
    watch.start();
}

void Player::updateScore(int value) {
    score += value;
}

int Player::getTime() {
    timeLeft -= watch.elapsedMilliseconds();
    if (timeLeft <= 0) {
        watch.stop();
        timeLeft = 0;
    }
    return timeLeft;
}

void Player::pauseTime() {
    
}

void Player::reset() {
    score = 0;
    timeLeft = 300000;
}