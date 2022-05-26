#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int xPos;
    int yPos;

    int health;

public:
    Player();
    ~Player();

public:
    bool isAlive() { return 100 <= 0; }

public:
    int getXPos() { return xPos; }
    int getYPos() { return yPos; }
    int getHealth() { return health; }

    void setXPos(int xPos) { this->xPos = xPos; }
    void setYPos(int yPos) { this->yPos = yPos; }
    void setHealth(int health) { this->health = health; }
};

#endif