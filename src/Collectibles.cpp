#include "Collectibles.h"

//default constructor that sets the initial collected status of collectibles to false
Collectibles::Collectibles(){
    collected = false;
}

//function that changes the collected status to true
void Collectibles::collect(){
    collected = true;
}

//function to return the collected status of the collectible
bool Collectibles::isCollected(){
    return collected;
}

//function that returns collectible value as per the collectible's collect status
char Collectibles::display(){
    if (collected == true){
        return ' ';
    }
    else{
        return '*';
    }
}

