//EnemyShip.h extends the Spaceship class and is used to create an enemy ship object
#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "SpaceShip.h"

class EnemyShip : public SpaceShip
{
public:
    EnemyShip();
    //move function for the enemy ship takes the player's position as a parameter array of floats
    void move(float playerPosition[3]);
    void setDirection(float playerPosition[3]);
    void update(float playerPosition[3]);

};

#endif
    
