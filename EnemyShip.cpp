//EnemyShip.cpp
#include "EnemyShip.h"
#include <GL/freeglut.h>


EnemyShip::EnemyShip()
    : SpaceShip(ENEMYSHIP) {
    // Additional initialization if needed
    // set the initial time since last to be with the creation of the spaceship
    timeSinceLastShot = glutGet(GLUT_ELAPSED_TIME);

    // set the time between shots to be 1.5 seconds
    timeBetweenShots = 2000;
}

void EnemyShip::move(float playerPosition[3], std::vector<Planet*> planets, std::vector<EnemyShip*> enemyShips) {
    // Function to normalize a direction vector and move the enemy ship only in the x and z axes
    auto moveInDirection = [this](float direction[3], float speed) {
        // Only consider x and z components for magnitude
        float magnitude = sqrt(direction[0] * direction[0] + direction[2] * direction[2]);
        if (magnitude > 0.0f) {
            direction[0] /= magnitude;
            direction[2] /= magnitude;
            setPosition(getPositionX() + direction[0] * speed, getPositionY(), getPositionZ() + direction[2] * speed);
        }
    };

    // Avoid other enemy ships
    float avoidDirection[3] = {0.0f, 0.0f, 0.0f};
    for (EnemyShip* enemy : enemyShips) {
        if (enemy != this) { // Avoid self-comparison
            float distance = sqrt(pow(enemy->getPositionX() - getPositionX(), 2) + pow(enemy->getPositionZ() - getPositionZ(), 2));
            if (distance < 900.0f) { // Threshold distance to avoid
                avoidDirection[0] += getPositionX() - enemy->getPositionX();
                avoidDirection[2] += getPositionZ() - enemy->getPositionZ();
            }
        }
    }

    // Avoid planets
    float closestDistance = 1000000.0f;
    Planet* closestPlanet = nullptr;
    for (Planet* planet : planets) {
        float distance = sqrt(pow(planet->getPositionX() - getPositionX(), 2) + pow(planet->getPositionZ() - getPositionZ(), 2));
        if (distance < closestDistance) {
            closestDistance = distance;
            closestPlanet = planet;
        }
    }

    if (closestPlanet && closestDistance < 600 + closestPlanet->getPlanetRadius()) {
        avoidDirection[0] += getPositionX() - closestPlanet->getPositionX();
        avoidDirection[2] += getPositionZ() - closestPlanet->getPositionZ();
    }

    // Normalize and apply avoidance direction if needed
    float avoidMagnitude = sqrt(avoidDirection[0] * avoidDirection[0] + avoidDirection[2] * avoidDirection[2]);
    if (avoidMagnitude > 0.0f) {
        avoidDirection[0] /= avoidMagnitude;
        avoidDirection[2] /= avoidMagnitude;
        moveInDirection(avoidDirection, 8.0f);
    }

    // Move towards the player to maintain exactly 1500 units distance
    float direction[3] = {
        playerPosition[0] - getPositionX(),
        0.0f, // Ignore y-axis movement
        playerPosition[2] - getPositionZ()
    };
    float magnitude = sqrt(direction[0] * direction[0] + direction[2] * direction[2]);
    if (magnitude != 1500.0f) {
        direction[0] /= magnitude;
        direction[2] /= magnitude;
        float adjustment = (magnitude - 1500.0f) / magnitude; // Adjust proportionally to the speed
        moveInDirection(direction, adjustment * 7.0f); // Adjust speed as needed
    }
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
    setRotation(angle+180, 0.0f, 1.0f, 0.0f);
    updateFirstPersonView();
    updateThirdPersonView();

}

void EnemyShip::update(float playerPosition[3], std::vector<Planet*> planets ,std::vector<EnemyShip*> enemyShips,std::vector<GameObject*>& gameObjectsRef) {
    setDirection(playerPosition);
    fireWeapon(gameObjectsRef);
    move(playerPosition, planets,enemyShips);
}

int EnemyShip::getId() {
    return id;
}

void EnemyShip::setId(int id) {
    this->id = id;
}