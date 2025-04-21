#include "Movement.h"
#include "Maze.h"
#include "Player.h"
using namespace std;

//function that decides how the player moves in the maze as per the keys pressed
void Movement::movePlayer(Maze &maze, Player &player, char direction, string &statusMessage){

    //getting the current position of the player
    int currentPosX = player.getPosX();
    int currentPosY = player.getPosY();

    //checking for cosole if the character entered is WASD or not
    if (direction != 'w' && direction != 'W' &&
        direction != 's' && direction != 'S' &&
        direction != 'a' && direction != 'A' &&
        direction != 'd' && direction != 'D') {
        statusMessage = "WASD Keys only, please!";
        return;
    }

    //setting new position to the current position
    int newPosX = currentPosX;
    int newPosY = currentPosY;

    //updating the new position as per player's key choice
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

    //getting the maze size from the maze class
    int mazeSize = maze.getMaxSize();

    //Console-logic checking if new position is within bounds
    if (newPosX < 0 || newPosX >= mazeSize || newPosY < 0 || newPosY >= mazeSize) {
        statusMessage = "Moving out of Maze Grid!";
        return;
    }

    //getting the maze element of the player's position to find if it is a valid move
    char targetCell = maze.getMazeGrid(newPosX, newPosY);

    //Collision detection logic
    //Checking if new position is not a wall
    if (targetCell == '|' || targetCell == '-' || targetCell == '+') {
        statusMessage = "Cannot move there!";
        return;
    }

    //checking if the new position is a collectible and updating its status accordingly
    if (targetCell == '*' && !maze.collectibles[newPosY][newPosX].isCollected()){
        maze.collectibles[newPosY][newPosX].collect();
        player.updateScore();
        statusMessage = "You just increased points!";
    }
    else{
        statusMessage = "Moved";
    }

    //setting the player's new position
    player.setPosX(newPosX);
    player.setPosY(newPosY);
}
