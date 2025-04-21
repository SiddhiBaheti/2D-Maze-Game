#include "Maze.h"
#include "Enemy.h"
#include <iostream>
#include <fstream>

using namespace std;

//a default constructor that creates the maze layout
Maze::Maze(){
    createMazeLayout();
}

//function to get the maze size
int Maze::getMaxSize(){
    return maxSize;
}

void Maze::createMazeLayout(){
    //initializing the maze grid characters
    char easyLevel[maxSize][maxSize] = {
        {'+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+'},
        {'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','-','*','*','|'},
        {'|','*','*','-','-','-','*','*','*','*','-','-','-','*','*','-','-','-','*','|'},
        {'|','*','*','-','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},
        {'|','*','|','*','-','-','-','*','|','-','-','*','*','|','-','-','*','|','*','|'},
        {'|','*','|','*','*','|','*','*','|',' ',' ','|','*','|','*','*','*','|','*','|'},
        {'|','*','|','*','*','|','*','*','|','-','-','*','*','|','*','*','*','|','*','|'},
        {'|','*','*','*','*','|','*','*','|',' ',' ','|','*','|','*','*','*','|','*','|'},
        {'|','*','*','*','*','|','*','*','|','-','-','*','*','|','-','-','*','*','*','|'},
        {'|','-','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},
        {'|','*','*','-','-','-','-','*','*','*','-','-','-','*','*','-','-','-','*','|'},
        {'|','*','*','*','*','*','-','*','*','*','*','*','*','*','*','*','*','*','*','|'},
        {'|','*','|','-','*','*','*','*','|','*','*','|','*','|','*','*','*','*','*','|'},
        {'|','*','|','*','*','-','*','*','|','*','*','|','*','|','*','*','*','-','*','|'},
        {'|','*','-','-','*','*','*','-','|','*','-','|','*','|','-','-','*','*','*','|'},
        {'|','*','*','|','*','|','*','|','|','*','|','|','*','|','*','|','*','|','*','|'},
        {'|','*','-','|','*','|','*','-','-','*','-','-','*','|','*','|','*','|','*','|'},
        {'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},
        {'|','*','-','-','-','*','*','-','-','-','*','*','*','*','-','*','*','-','-','|'},
        {'+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+'}
    };

    //adding the elements to the mazeGrid
    for (int i = 0; i < maxSize; i++){
        for (int j = 0; j < maxSize; j++){
            mazeGrid[i][j] = easyLevel[i][j];
            //mapping the all the collectibles in the grid and initializing them as not collected
            if (mazeGrid[i][j] == '*'){
                collectibles[i][j] = Collectibles();
            }
        }
    }
    //saving the layout to a file
    saveToFile();
}

//function to save the maze to the file
void Maze::saveToFile(){
    //opening the file in write mode
    ofstream mazefile("Maze.txt");
    //checking if the file was opened successfully
    if(!mazefile){
        cerr<<"Error opening the file!"<<endl;
        return;
    }

    //writing the maze grid to the file
    for (int i = 0; i < maxSize; i++){
        for (int j = 0; j < maxSize; j++){
            mazefile<<mazeGrid[i][j];
        }
        mazefile<<'\n';
    }

    //closing the file
    mazefile.close();
}

//function to read from the maze file
void Maze::loadFromFile(){
    //opening the maze file to read
    ifstream mazefile("Maze.txt");
    //checking if the file was opened successfully
    if (!mazefile){
        cerr<<"Maze file not found! Generating default layout.\n";
        createMazeLayout();
        return;
    }

    //writing each character of the file to the mazeGrid character array
    for (int i = 0; i < maxSize; i++){
        for (int j = 0; j < maxSize; j++){
            mazefile.get(mazeGrid[i][j]);
        }
        mazefile.ignore();//ignoring any newline characters
    }

    mazefile.close();//closing the file
}

//function to display the maze in console
void Maze::displayMaze(const string &statusMessage, const Player &player, const Enemy &enemy){
    //to display the score
    cout<<endl<<"Your Score: "<<player.getScore()<<endl;

    for (int i = 0; i < maxSize; i++) {
        for (int j = 0; j < maxSize; j++) {
            //displaying the player position in the maze as 'P'
            if (i == player.getPosY() && j == player.getPosX()){
                cout<<'P'<<" ";
            }
            //displaying enemy as 'X'
            else if(i == enemy.getPosY() && j == enemy.getPosX()){
                cout<<'X'<<" ";
            }
            //if the player lands on the collectible then removing it and updating its status as taken
            else if (mazeGrid[i][j] == '*'){
                cout<<collectibles[i][j].display()<<" ";
            }
            //displaying the grid elements as in array
            else{
                cout << mazeGrid[i][j] << " ";
            }
        }
        cout << endl;
    }

    //displaying the status message
    cout << endl << statusMessage << endl;
}

//function that returns the maze element as per the x, y coordinates
char Maze::getMazeGrid(int x, int y){
    return mazeGrid[y][x];
}

//setting value to the desired cell with x and y coordinates
void Maze::setMazeGrid(int x, int y, char value){
    mazeGrid[y][x] = value;
}





