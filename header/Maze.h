//Maze.h
#ifndef MAZE_H
#define MAZE_H

#include <string>
#include "Collectibles.h"
#include "Player.h"

using namespace std;

class Enemy;

class Maze{
private:
    static const int maxSize = 10;
    char mazeGrid[maxSize][maxSize];
public:
    Collectibles collectibles[maxSize][maxSize];

    Maze();
    void createMazeLayout();
    void displayMaze(const string &statusMessage, const Player &player, const Enemy &enemy);
    char getMazeGrid(int x, int y);
    void setMazeGrid(int x, int y, char value);
};

#endif // MAZE_H
