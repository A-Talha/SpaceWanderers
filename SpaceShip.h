#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "GameObject.h"

class SpaceShip : public GameObject {
public:
    // Constructor
    SpaceShip();

    // Additional methods specific to SpaceShip
    void fireWeapon();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void RotateRight();
    void RotateLeft();

private:
    // Additional attributes specific to SpaceShip
    int weaponPower;
    float moveSpeed;
    float rotationSpeed;
    
};

#endif