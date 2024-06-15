#include "FireBullet.h"
#include <vector>
#include <ctime>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

// Constructor
FireBullet::FireBullet(int firePower, std::vector<float> position, std::vector<float> lookAt, std::vector<GameObject*>& objectsRef)
    : GameObject(FIREBULLET), firePower(firePower), moveSpeed(40.0f), gameObjectsRef(objectsRef) {
    direction[0] = lookAt[0] - position[0];
    direction[2] = lookAt[2] - position[2];

    // Normalize direction vector
    float magnitude = std::sqrt(direction[0] * direction[0] + direction[2] * direction[2]);
    direction[0] /= magnitude;
    direction[2] /= magnitude;

    setPosition(position[0] + 50 * direction[0], position[1], position[2] + 50 * direction[2]);

    initialPosition[0] = position[0];
    initialPosition[2] = position[2];
}

void FireBullet::draw()
{
    glPushMatrix();
    glTranslatef(getPositionX(), getPositionY(), getPositionZ());
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(20, 50, 50);
    glPopMatrix();
}

// Method to update the location of the FireBullet based on direction and moveSpeed
void FireBullet::update() {
    // check if distance between current position and initial position more than 2000 to delete the element from the gameobjects reference vetor and delete the object from memory
    float distance = std::sqrt((getPositionX() - initialPosition[0]) * (getPositionX() - initialPosition[0]) + (getPositionZ() - initialPosition[2]) * (getPositionZ() - initialPosition[2]));
    if (distance > 15000) {
        // Find the element in the gameObjectsRef vector and erase it
        for (auto it = gameObjectsRef.begin(); it != gameObjectsRef.end(); ++it) {
            if (*it == this) {
                gameObjectsRef.erase(it);
                break;
            }
        }
        // Delete the object from memory
        delete this;
    }
    setPosition(getPositionX() + direction[0] * moveSpeed, getPositionY(), getPositionZ() + direction[2] * moveSpeed);
}