//EnemyShip.h extends the Spaceship class and is used to create an enemy ship object
#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "SpaceShip.h"
#include "Planet.h"
#include <math.h>
#include <iostream>
using namespace std;

class EnemyShip : public SpaceShip
{
public:
    EnemyShip();
    //move function for the enemy ship takes the player's position as a parameter array of floats
    void move(float playerPosition[3], std::vector<Planet*> planets, std::vector<EnemyShip*> enemyShips);
    void setDirection(float playerPosition[3]);
    //update function for the enemy ship takes the player's position as a parameter array of floats and takes a vector of planets as a parameter
    void update(float playerPosition[3], std::vector<Planet*> planets, std::vector<EnemyShip*> enemyShips);

    //getters and setters for the id of the enemy ship
    int getId() ;
    void setId(int id) ;
private:
    int id;

};

#endif
    
