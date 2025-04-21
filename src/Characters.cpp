#include "Characters.h"

//default constructor to set the initial values
Characters::Characters(int x, int y){
    posX = x;
    posY = y;
}

//function to return the current x - coordinates (column number)
int Characters::getPosX() const{
    return posX;
}

//function to return the current y - coordinates (row number)
int Characters::getPosY() const{
    return posY;
}

//function to set the current x - coordinates
void Characters::setPosX(int x){
    posX = x;
}

//function to set the current y - coordinates
void Characters::setPosY(int y){
    posY = y;
}
