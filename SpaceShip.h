#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "GameObject.h"

class SpaceShip : public GameObject {
public:
    // Constructor
    SpaceShip();
    SpaceShip(ObjectType type);

    // Additional methods specific to SpaceShip
    void draw() override;
    void fireWeapon(std::vector<GameObject*>& gameObjects);
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

    // Getters
    int getWeaponPower();
    int getHealth();
    float getMoveSpeed();
    float getRotationSpeed();

    // Setters
    void setWeaponPower(int power);
    void setHealth(int health);
    void setMoveSpeed(float speed);
    void setRotationSpeed(float speed);

    void onCollisionEnter(GameObject *other);
    void receiveDamage(int damage);

private:
    // Additional attributes specific to SpaceShip
    int weaponPower;
    int health;
    float moveSpeed;
    float rotationSpeed;
    std::vector<float> firstPersonCameraPosition = {0.0f, 0.0f, 0.0f}; // x, y, z
    std::vector<float> firstPersonLookAt = {0.0f, 0.0f, -1.0f}; // x, y, z
    std::vector<float> thirdPersonCameraPosition = {0.0f, 0.0f, 0.0f}; // x, y, z
    std::vector<float> thirdPersonLookAt = {0.0f, 0.0f, -1.0f}; // x, y, z
    
    
};

#endif