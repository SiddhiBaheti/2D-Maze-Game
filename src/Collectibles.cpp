#include "Collectibles.h"

Collectibles::Collectibles(){
    collected = false;
}

void Collectibles::collect(){
    collected = true;
}

bool Collectibles::isCollected(){
    return collected;
}

char Collectibles::display(){
    if (collected == true){
        return ' ';
    }
    else{
        return '*';
    }
}

