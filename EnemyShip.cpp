//EnemyShip.cpp
#include "EnemyShip.h"
#include <math.h>

EnemyShip::EnemyShip()
    : SpaceShip(ENEMYSHIP) {
    // Additional initialization if needed
}

void EnemyShip::move(float playerPosition[3]) {
    // Implement enemy ship movement logic here
    // For example, move towards the player's position
    // You can access the player's position using the playerPosition array
}

void EnemyShip::setDirection(float playerPosition[3]) {
    //get the direction vector from the enemy ship to the player
    float direction[3] = {
        playerPosition[0] - getPositionX(),
        playerPosition[1] - getPositionY(),
        playerPosition[2] - getPositionZ()
    };

    //normalize the direction vector
    float magnitude = sqrt(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);
    direction[0] /= magnitude;
    direction[1] /= magnitude;
    direction[2] /= magnitude;

    //set the rotation of the enemy ship to face the player
    float angle = atan2(direction[0], direction[2]) * 180 / 3.14159;
    setRotation(angle, 0.0f, 1.0f, 0.0f);
}

void EnemyShip::update(float playerPosition[3]) {
    setDirection(playerPosition);
    move(playerPosition);
}