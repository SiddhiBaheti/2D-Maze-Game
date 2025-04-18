#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "Maze.h"
#include "Player.h"
#include "Enemy.h"
#include "Movement.h"

using namespace std;

int main(){
    srand(time(0));

    Maze maze;
    Player player;
    Enemy enemy;
    Movement mover;
    string statusMessage = "Welcome to the Maze! Press W A S D for movement and Q for exit.";
    char input;

    maze.createMazeLayout();

    while (true){
        system("CLS");
        maze.displayMaze(statusMessage, player, enemy);
        if (player.getPosX() == enemy.getPosX() && player.getPosY() == enemy.getPosY()){
            cout<<"\nGame Over! The enemy caught you!"<<endl;
            break;
        }

        cout<<"Press W A S D to move and Q for exit.";
        input = getch();

        if (input == 'q' || input == 'Q'){
            break;
        }
        mover.movePlayer(maze, player, input, statusMessage);
        enemy.moveEnemy(maze);

    }

    cout<<"\nFinal Score: "<<player.getScore()<<endl;

    return 0;
}
