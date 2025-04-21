//Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Characters.h"

class Maze;

class Enemy: public Characters{
public:
    Enemy(int x, int y);
    void moveEnemy(Maze &maze);
};

#endif // ENEMY_H
