#include "SpaceShip.h"
#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include "FireBullet.h"

SpaceShip::SpaceShip()
    : GameObject(SPACESHIP), weaponPower(100), moveSpeed(100.0f), rotationSpeed(5.0f) {
    // Additional initialization if needed
    // set the initial time since last to be with the creation of the spaceship
    bounding_sphere_radius = 400.0f;
    timeSinceLastShot = glutGet(GLUT_ELAPSED_TIME);

    // set the time between shots to be 0.5 seconds
    timeBetweenShots = 500;
}

SpaceShip::SpaceShip(ObjectType type)
    : GameObject(type), weaponPower(100), moveSpeed(100.0f), rotationSpeed(5.0f){
    // Additional initialization if needed
    // set the initial time since last to be with the creation of the spaceship
    bounding_sphere_radius = 400.0f;
    timeSinceLastShot = glutGet(GLUT_ELAPSED_TIME);

    // set the time between shots to be 0.5 seconds
    timeBetweenShots = 500;
}

void SpaceShip::fireWeapon(std::vector<GameObject*>& gameObjectsRef) {
    // Check if enough time has passed since the last shot
    if (glutGet(GLUT_ELAPSED_TIME) - timeSinceLastShot < timeBetweenShots) {
        return;
    }
    timeSinceLastShot = glutGet(GLUT_ELAPSED_TIME);
    std::cout << "Firing weapon with power: " << weaponPower << std::endl;
    FireBullet* fireBullet = new FireBullet(weaponPower, getFirstPersonCameraPosition(), getFirstPersonLookAt(), gameObjectsRef);

    gameObjectsRef.push_back(fireBullet);
}

void SpaceShip::draw() {
    // Call the base class GameObject draw function
    GameObject::draw();

    // Apply transformations
    glPushMatrix();
    applyTransformations();

    // Draw the main body (cuboid)
    glColor3f(0.8f, 0.0f, 0.0f); // Red color for the main body
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(-200.0f, 75.0f, -400.0f);
    glVertex3f(200.0f, 75.0f, -400.0f);
    glVertex3f(200.0f, -75.0f, -400.0f);
    glVertex3f(-200.0f, -75.0f, -400.0f);
    // Back face
    glVertex3f(-200.0f, 75.0f, 400.0f);
    glVertex3f(200.0f, 75.0f, 400.0f);
    glVertex3f(200.0f, -75.0f, 400.0f);
    glVertex3f(-200.0f, -75.0f, 400.0f);
    // Top face
    glVertex3f(-200.0f, 75.0f, -400.0f);
    glVertex3f(200.0f, 75.0f, -400.0f);
    glVertex3f(200.0f, 75.0f, 400.0f);
    glVertex3f(-200.0f, 75.0f, 400.0f);
    // Bottom face
    glVertex3f(-200.0f, -75.0f, -400.0f);
    glVertex3f(200.0f, -75.0f, -400.0f);
    glVertex3f(200.0f, -75.0f, 400.0f);
    glVertex3f(-200.0f, -75.0f, 400.0f);
    // Left face
    glVertex3f(-200.0f, 75.0f, -400.0f);
    glVertex3f(-200.0f, -75.0f, -400.0f);
    glVertex3f(-200.0f, -75.0f, 400.0f);
    glVertex3f(-200.0f, 75.0f, 400.0f);
    // Right face
    glVertex3f(200.0f, 75.0f, -400.0f);
    glVertex3f(200.0f, -75.0f, -400.0f);
    glVertex3f(200.0f, -75.0f, 400.0f);
    glVertex3f(200.0f, 75.0f, 400.0f);
    glEnd();

    // Draw cockpit
    glColor3f(0.0f, 0.5f, 0.5f); // Cyan color for cockpit
    glBegin(GL_QUADS);
    glVertex3f(-50.0f, 75.0f, -250.0f);
    glVertex3f(50.0f, 75.0f, -250.0f);
    glVertex3f(50.0f, 150.0f, -150.0f);
    glVertex3f(-50.0f, 150.0f, -150.0f);
    glEnd();

    // Draw wings
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color for wings
    glBegin(GL_TRIANGLES);
    // Left wing
    glVertex3f(-200.0f, 0.0f, -100.0f);
    glVertex3f(-400.0f, 0.0f, 0.0f);
    glVertex3f(-200.0f, 0.0f, 100.0f);
    // Right wing
    glVertex3f(200.0f, 0.0f, -100.0f);
    glVertex3f(400.0f, 0.0f, 0.0f);
    glVertex3f(200.0f, 0.0f, 100.0f);
    glEnd();

    // Draw engines
    glColor3f(0.8f, 0.0f, 0.0f); // Red color for engines
    glBegin(GL_QUADS);
    // Bottom engine
    glVertex3f(-50.0f, -75.0f, 400.0f);
    glVertex3f(50.0f, -75.0f, 400.0f);
    glVertex3f(50.0f, -150.0f, 400.0f);
    glVertex3f(-50.0f, -150.0f, 400.0f);
    // Top engine
    glVertex3f(-50.0f, 75.0f, 400.0f);
    glVertex3f(50.0f, 75.0f, 400.0f);
    glVertex3f(50.0f, 150.0f, 400.0f);
    glVertex3f(-50.0f, 150.0f, 400.0f);
    glEnd();

    // Apply texture (optional)
    if (texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_TEXTURE_2D);

        glBegin(GL_QUADS);
        // Apply texture to front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-200.0f, -75.0f, -400.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(200.0f, -75.0f, -400.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(200.0f, 75.0f, -400.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-200.0f, 75.0f, -400.0f);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

    // Use shader (optional)
    if (shader) {
        glUseProgram(shader);

        // Draw the spaceship with the shader applied
        glBegin(GL_QUADS);
        // Example shader effect on the top face
        glColor3f(0.0f, 0.8f, 0.8f); // Cyan color for top face
        glVertex3f(-200.0f, 75.0f, -400.0f);
        glVertex3f(200.0f, 75.0f, -400.0f);
        glVertex3f(200.0f, 75.0f, 400.0f);
        glVertex3f(-200.0f, 75.0f, 400.0f);
        glEnd();

        glUseProgram(0);
    }

    glPopMatrix();
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
    thirdPersonCameraPosition[0] = getPositionX() - 1500 * sin(-getRotationAngle() * 3.14159 / 180);
    thirdPersonCameraPosition[1] = getPositionY() + 600;
    thirdPersonCameraPosition[2] = getPositionZ() + 1500 * cos(-getRotationAngle() * 3.14159 / 180);

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

void SpaceShip::onCollisionEnter(GameObject* other){
    if(other->getType() == PLANET){
        GameObject::Destroy(this);
    }
}

void SpaceShip::receiveDamage(int damage)
{
    health -= damage;
    if(health <= 0)
        GameObject::Destroy(this);
}
