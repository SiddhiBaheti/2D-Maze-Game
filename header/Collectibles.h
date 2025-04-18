//Collectibles.h

#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H

class Collectibles{
private:
    bool collected;
public:
    Collectibles();
    void collect();
    bool isCollected();
    char display();
};

#endif // COLLECTIBLES_H
