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
    void updateFirstPersonView();
    void updateThirdPersonView();
    std::vector<float> getFirstPersonCameraPosition();
    std::vector<float> getFirstPersonLookAt();
    std::vector<float> getThirdPersonCameraPosition();
    std::vector<float> getThirdPersonLookAt();


private:
    // Additional attributes specific to SpaceShip
    int weaponPower;
    float moveSpeed;
    float rotationSpeed;
    std::vector<float> firstPersonCameraPosition = {0.0f, 0.0f, 0.0f}; // x, y, z
    std::vector<float> firstPersonLookAt = {0.0f, 0.0f, -1.0f}; // x, y, z
    std::vector<float> thirdPersonCameraPosition = {0.0f, 0.0f, 0.0f}; // x, y, z
    std::vector<float> thirdPersonLookAt = {0.0f, 0.0f, -1.0f}; // x, y, z
    
    
};

#endif