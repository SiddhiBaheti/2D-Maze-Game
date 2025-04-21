//Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Characters.h"
#include <string>
using namespace std;

class Player: public Characters{
private:
    int score;
    //string playerName;

public:
    Player();

    int getScore() const;
    void updateScore();
    void setScore(int levelScore);
    void setPlayerName(string name, int score);
    void saveToFile(string name, int score);
};

#endif // PLAYER_H
