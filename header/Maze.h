//Maze.h
#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Collectibles.h"
#include "Player.h"

using namespace std;

class Enemy;

class Maze{
private:
    static const int maxSize = 20;
    char mazeGrid[maxSize][maxSize];

public:
    Collectibles collectibles[maxSize][maxSize];

    Maze();
    int getMaxSize();
    void createMazeLayout();
    void saveToFile();
    void loadFromFile();
    void displayMaze(const string &statusMessage, const Player &player, const Enemy &enemy);
    char getMazeGrid(int x, int y);
    void setMazeGrid(int x, int y, char value);
};

#endif // MAZE_H
