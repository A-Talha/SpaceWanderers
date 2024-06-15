#include "Planet.h"
#include <GL/glut.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

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
    glScalef(-1.0f, 1.0f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

    if (textureID != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);

    glColor3f(planetColor[0], planetColor[1], planetColor[2]);
    gluSphere(quad, planetRadius, 50, 50);

    gluDeleteQuadric(quad);

    if (textureID != 0) glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void Planet::update()
{
    // Update planet center according to orbit speed within the orbit radius
    orbitAngle += orbitSpeed;
    if (orbitAngle > 360.0f) orbitAngle -= 360.0f;
    center[0] = orbitRadius * cos(orbitAngle);
    center[2] = orbitRadius * sin(orbitAngle);
}

void Planet::loadTexture(const char* filepath)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture: " << filepath << std::endl;
    }
    stbi_image_free(data);
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
void Planet::setPlanetRadius(float radius) { planetRadius = radius; bounding_sphere_radius = radius; }
void Planet::setOrbitRadius(float radius) { orbitRadius = radius; }
void Planet::setOrbitSpeed(float speed) { orbitSpeed = speed; }
void Planet::setRotationSpeed(float speed) { rotationSpeed = speed; }
void Planet::setAngle(float angle) { this->angle = angle; }
void Planet::setOrbitAngle(float angle) { orbitAngle = angle; }
void Planet::setCenter(const std::vector<float>& center) { this->center = center; }
void Planet::setPlanetColor(const std::vector<float>& color) { planetColor = color; }

