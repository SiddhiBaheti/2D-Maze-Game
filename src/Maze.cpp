#include "Maze.h"
#include "Enemy.h"
#include <iostream>

using namespace std;

Maze::Maze(){
    createMazeLayout();
}

void Maze::createMazeLayout(){
    char easyLevel[maxSize][maxSize] = {
        {'+','-','-','-','+','-','-','-','-','+'},
        {'|','*','*','*','|','*','*','*','*','|'},
        {'|','*','|','*','|','*','|','*','*','|'},
        {'|','*','|','*','*','*','|','*','|','|'},
        {'|','*','+','-','+','-','*','*','*','|'},
        {'|','*','|','*','*','*','|','*','*','|'},
        {'|','*','|','*','|','*','|','*','|','|'},
        {'|','*','*','*','|','*','*','*','*','|'},
        {'|','*','*','|','|','|','*','*','*','|'},
        {'+','-','-','+','+','+','-','-','-','+'}
    };

    for (int i = 0; i < maxSize; i++){
        for (int j = 0; j < maxSize; j++){
            mazeGrid[i][j] = easyLevel[i][j];
            if (mazeGrid[i][j] == '*'){
                collectibles[i][j] = Collectibles();
            }
        }
    }
}

void Maze::displayMaze(const string &statusMessage, const Player &player, const Enemy &enemy){
    cout<<endl<<"Your Score: "<<player.getScore()<<endl;

    for (int i = 0; i < maxSize; i++) {
        for (int j = 0; j < maxSize; j++) {

            if (i == player.getPosY() && j == player.getPosX()){
                cout<<'P'<<" ";
            }
            else if(i == enemy.getPosY() && j == enemy.getPosX()){
                cout<<'X'<<" ";
            }
            else if (mazeGrid[i][j] == '*'){
                cout<<collectibles[i][j].display()<<" ";
            }
            else{
                cout << mazeGrid[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << endl << statusMessage << endl;
}

char Maze::getMazeGrid(int x, int y){
    return mazeGrid[y][x];
}

void Maze::setMazeGrid(int x, int y, char value){
    mazeGrid[y][x] = value;
}
