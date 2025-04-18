#include "Player.h"
#include <iostream>

Player::Player(): Characters(1,1){
    score = 0;
}

int Player::getScore() const{
    return score;
}

void Player::updateScore(){
    score += 10;
}
