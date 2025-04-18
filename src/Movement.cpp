#include "Movement.h"
#include "Maze.h"
#include "Player.h"
using namespace std;

void Movement::movePlayer(Maze &maze, Player &player, char direction, string &statusMessage){
    int currentPosX = player.getPosX();
    int currentPosY = player.getPosY();

    if (direction != 'w' && direction != 'W' &&
        direction != 's' && direction != 'S' &&
        direction != 'a' && direction != 'A' &&
        direction != 'd' && direction != 'D') {
        statusMessage = "WASD Keys only, please!";
        return;
    }

    int newPosX = currentPosX;
    int newPosY = currentPosY;

    if (direction == 'w' || direction == 'W'){
        newPosY--;
    }
    else if (direction == 's' || direction == 'S'){
        newPosY++;
    }
    else if (direction == 'a' || direction == 'A'){
        newPosX--;
    }
    else if (direction == 'd' || direction == 'D'){
        newPosX++;
    }

    // Check if new position is within bounds
    if (newPosX < 0 || newPosX >= 10 || newPosY < 0 || newPosY >= 10) {
        statusMessage = "Moving out of Maze Grid!";
        return;
    }

    char targetCell = maze.getMazeGrid(newPosX, newPosY);

    // Check if new position is not a wall
    if (targetCell == '|' || targetCell == '-' || targetCell == '+') {
        statusMessage = "Cannot move there!";
        return;
    }

    if (targetCell == '*' && !maze.collectibles[newPosY][newPosX].isCollected()){
        maze.collectibles[newPosY][newPosX].collect();
        player.updateScore();
        statusMessage = "You just increased points!";
    }
    else{
        statusMessage = "Moved";
    }

    player.setPosX(newPosX);
    player.setPosY(newPosY);
}
