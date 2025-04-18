#include "Enemy.h"
#include "Maze.h"
#include <cstdlib>

Enemy::Enemy(): Characters(8, 8){}

void Enemy::moveEnemy(Maze &maze){
    int directions[4][2] = {
        {0, 1}, //Up
        {0, -1}, //Down
        {1, 0}, //Right
        {-1, 0} //Left
    };

    for (int i = 0; i < 4; i++){
        int dir = rand() % 4;
        int newX = posX + directions[dir][0];
        int newY = posY + directions[dir][1];

        if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10 &&
            maze.getMazeGrid(newX, newY) != '|' &&
            maze.getMazeGrid(newX, newY) != '-' &&
            maze.getMazeGrid(newX, newY) != '+')
            {
                posX = newX;
                posY = newY;
                break;
            }
    }
}
