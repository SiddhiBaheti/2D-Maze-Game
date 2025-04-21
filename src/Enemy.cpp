#include "Enemy.h"
#include "Maze.h"
#include <cstdlib>

//default constructor to initialize the enemy positions
Enemy::Enemy(int x, int y): Characters(x, y){}

//function to move enemies randomly in the maze
void Enemy::moveEnemy(Maze &maze){
    //getting maze size
    int mazeSize = maze.getMaxSize();

    //defining the possible directions for the enemy
    int directions[4][2] = {
        {0, 1}, //Up
        {0, -1}, //Down
        {1, 0}, //Right
        {-1, 0} //Left
    };

    for (int i = 0; i < 4; i++){
        //randomly choosing one of the four directions
        int dir = rand() % 4;
        //changing the position as per it
        int newX = posX + directions[dir][0];
        int newY = posY + directions[dir][1];

        //logic for preventing the enemy to run into walls
        if (newX >= 0 && newX < mazeSize && newY >= 0 && newY < mazeSize &&
            maze.getMazeGrid(newX, newY) != '|' &&
            maze.getMazeGrid(newX, newY) != '-' &&
            maze.getMazeGrid(newX, newY) != '+')
            {
                //updating enemy position if the chosen direction is valid
                posX = newX;
                posY = newY;
                break;
            }
    }
}
