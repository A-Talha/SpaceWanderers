#include "SpaceShip.h"
#include <iostream>
#include <cmath>

SpaceShip::SpaceShip()
    : GameObject(SPACESHIP), weaponPower(100), moveSpeed(100.0f), rotationSpeed(5.0f) {
    // Additional initialization if needed
}

SpaceShip::SpaceShip(ObjectType type)
    : GameObject(type), weaponPower(100), moveSpeed(100.0f), rotationSpeed(5.0f) {
    // Additional initialization if needed
}

void SpaceShip::fireWeapon() {
    std::cout << "Firing weapon with power: " << weaponPower << std::endl;
    // Implement the firing logic here
}

void SpaceShip::moveForward() {
    setPosition(
        getPositionX() + moveSpeed * sin(-getRotationAngle() * 3.14159 / 180),
        getPositionY(),
        getPositionZ() - moveSpeed * cos(-getRotationAngle() * 3.14159 / 180)
    );
}

void SpaceShip::moveBackward() {
    setPosition(
        getPositionX() - moveSpeed * sin(-getRotationAngle() * 3.14159 / 180),
        getPositionY(),
        getPositionZ() + moveSpeed * cos(-getRotationAngle() * 3.14159 / 180)
    );
}

void SpaceShip::moveLeft() {
    setPosition(
        getPositionX() - moveSpeed * sin(-(getRotationAngle() * 3.14159 / 180) + 3.14159 / 2),
        getPositionY(),
        getPositionZ() + moveSpeed * cos(-(getRotationAngle() * 3.14159 / 180) + 3.14159 / 2)
    );
}

void SpaceShip::moveRight() {
    setPosition(
        getPositionX() - moveSpeed * sin(-(getRotationAngle() * 3.14159 / 180) - 3.14159 / 2),
        getPositionY(),
        getPositionZ() + moveSpeed * cos(-(getRotationAngle() * 3.14159 / 180) - 3.14159 / 2)
    );
}

void SpaceShip::RotateRight() {
    setRotation(getRotationAngle() - rotationSpeed, 0.0f, 1.0f, 0.0f);
}

void SpaceShip::RotateLeft() {
    setRotation(getRotationAngle() + rotationSpeed, 0.0f, 1.0f, 0.0f);
}

void SpaceShip::updateFirstPersonView() {
    // Implement the first person view logic here
    firstPersonCameraPosition[0] = getPositionX() + 405 * sin(-getRotationAngle() * 3.14159 / 180);
    firstPersonCameraPosition[1] = getPositionY();
    firstPersonCameraPosition[2] = getPositionZ() - 405 * cos(-getRotationAngle() * 3.14159 / 180);

    firstPersonLookAt[0] = getPositionX() + 455 * sin(-getRotationAngle() * 3.14159 / 180);
    firstPersonLookAt[1] = getPositionY();
    firstPersonLookAt[2] = getPositionZ() - 455 * cos(-getRotationAngle() * 3.14159 / 180);
}

void SpaceShip::updateThirdPersonView() {
    // Implement the third person view logic here
    thirdPersonCameraPosition[0] = getPositionX() - 1200 * sin(-getRotationAngle() * 3.14159 / 180);
    thirdPersonCameraPosition[1] = getPositionY() + 500;
    thirdPersonCameraPosition[2] = getPositionZ() + 1200 * cos(-getRotationAngle() * 3.14159 / 180);

    thirdPersonLookAt[0] = getPositionX();
    thirdPersonLookAt[1] = getPositionY();
    thirdPersonLookAt[2] = getPositionZ();
}

std::vector<float> SpaceShip::getFirstPersonCameraPosition() {
    return firstPersonCameraPosition;
}

std::vector<float> SpaceShip::getFirstPersonLookAt() {
    return firstPersonLookAt;
}

std::vector<float> SpaceShip::getThirdPersonCameraPosition() {
    return thirdPersonCameraPosition;
}

std::vector<float> SpaceShip::getThirdPersonLookAt() {
    return thirdPersonLookAt;
}

int SpaceShip::getWeaponPower() {
    return weaponPower;
}

int SpaceShip::getHealth() {
    return health;
}

float SpaceShip::getMoveSpeed() {
    return moveSpeed;
}

float SpaceShip::getRotationSpeed() {
    return rotationSpeed;
}

void SpaceShip::setWeaponPower(int power) {
    weaponPower = power;
}

void SpaceShip::setHealth(int h) {
    health = h;
}

void SpaceShip::setMoveSpeed(float speed) {
    moveSpeed = speed;
}

void SpaceShip::setRotationSpeed(float speed) {
    rotationSpeed = speed;
}



