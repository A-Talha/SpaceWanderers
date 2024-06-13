#include "Planet.h"
#include <GL/glut.h>

Planet::Planet() : GameObject(PLANET)
{
    planetRadius = 0.0f;
    orbitRadius = 0.0f;
    orbitSpeed = 0.0f;
    rotationSpeed = 0.0f;
    angle = 0.0f;
    orbitAngle = 0.0f;
    center = {0.0f, 0.0f, 0.0f};
    planetColor = {1.0f, 1.0f, 1.0f}; // Default white color
}

void Planet::draw()
{
    glPushMatrix();
    glTranslatef(center[0], center[1], center[2]);
    glColor3f(planetColor[0], planetColor[1], planetColor[2]);
    glutSolidSphere(planetRadius, 50, 50);
    glPopMatrix();
}

// Getters
float Planet::getPlanetRadius() const { return planetRadius; }
float Planet::getOrbitRadius() const { return orbitRadius; }
float Planet::getOrbitSpeed() const { return orbitSpeed; }
float Planet::getRotationSpeed() const { return rotationSpeed; }
float Planet::getAngle() const { return angle; }
float Planet::getOrbitAngle() const { return orbitAngle; }
std::vector<float> Planet::getCenter() const { return center; }
std::vector<float> Planet::getPlanetColor() const { return planetColor; }

// Setters
void Planet::setPlanetRadius(float radius) { planetRadius = radius; }
void Planet::setOrbitRadius(float radius) { orbitRadius = radius; }
void Planet::setOrbitSpeed(float speed) { orbitSpeed = speed; }
void Planet::setRotationSpeed(float speed) { rotationSpeed = speed; }
void Planet::setAngle(float angle) { this->angle = angle; }
void Planet::setOrbitAngle(float angle) { orbitAngle = angle; }
void Planet::setCenter(const std::vector<float>& center) { this->center = center; }
void Planet::setPlanetColor(const std::vector<float>& color) { planetColor = color; }
