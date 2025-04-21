#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//default constructor to initialize the player position and score
Player::Player(): Characters(1,1){
    score = 0;
}

//function to return the player's current score
int Player::getScore() const{
    return score;
}

//function that updates the score of player
void Player::updateScore(){
    score += 10;
}

//function to set the level final score
void Player::setScore(int levelScore){
    score = levelScore;
}

//function to set the player's name
void Player::setPlayerName(string name, int score){
    string playerName = name;
    int finalScore = score;
}

//function to store player name and their score in the file
void Player::saveToFile(string name, int score){
    //opening file to write in append mode
    ofstream scoreFile("Scores.txt", ios::app);
    if(!scoreFile){
        cerr<<"Error opening the file!"<<endl;
        return;
    }

    //writing the name and score to the file
    scoreFile << name<<' '<<score<<'\n';

    scoreFile.close();
}

