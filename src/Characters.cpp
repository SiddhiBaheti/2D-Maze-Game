#include "Characters.h"

Characters::Characters(int x, int y){
    posX = x;
    posY = y;
}

int Characters::getPosX() const{
    return posX;
}

int Characters::getPosY() const{
    return posY;
}

void Characters::setPosX(int x){
    posX = x;
}

void Characters::setPosY(int y){
    posY = y;
}
