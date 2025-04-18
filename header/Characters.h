//Characters.h
#ifndef CHARACTERS_H
#define CHARACTERS_H

class Characters{
protected:
    int posX, posY;
public:
    Characters(int x, int y);

    int getPosX() const;
    int getPosY() const;

    void setPosX(int x);
    void setPosY(int y);
};
#endif // CHARACTERS_H
