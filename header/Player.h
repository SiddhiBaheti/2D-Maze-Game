//Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Characters.h"

class Player: public Characters{
private:
    int score;

public:
    Player();

    int getScore() const;
    void updateScore();
};

#endif // PLAYER_H
