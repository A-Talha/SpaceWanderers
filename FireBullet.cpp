#include "FireBullet.h"
#include <vector>
#include <ctime>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

// Constructor
FireBullet::FireBullet(int firePower, std::vector<float> position, std::vector<float> lookAt)
    : GameObject(FIREBULLET), firePower(firePower), moveSpeed(20.0f) {
    direction[0] = lookAt[0] - position[0];
    direction[2] = lookAt[2] - position[2];

    // Normalize direction vector
    float magnitude = std::sqrt(direction[0] * direction[0] + direction[2] * direction[2]);
    direction[0] /= magnitude;
    direction[2] /= magnitude;

    setPosition(position[0] + 50 * direction[0], position[1], position[2] + 50 * direction[2]);
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
    setPosition(getPositionX() + direction[0] * moveSpeed, getPositionY(), getPositionZ() + direction[2] * moveSpeed);
}
