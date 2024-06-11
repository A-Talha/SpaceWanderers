#include "SpaceShip.h"
#include <iostream>
#include <cmath>

SpaceShip::SpaceShip()
    : GameObject(SPACESHIP), weaponPower(100), moveSpeed(100.0f), rotationSpeed(5.0f) {
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
