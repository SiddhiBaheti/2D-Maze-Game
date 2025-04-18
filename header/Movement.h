//Movement.h

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Maze.h"
#include "Player.h"
#include <string>

using namespace std;

class Movement{
public:
    void movePlayer(Maze &maze, Player &player, char direction, string &statusMessage);
};

#endif // MOVEMENT_H
