#ifndef PLANET_H
#define PLANET_H

#include "GameObject.h"
#include <vector>

class Planet : public GameObject
{
public:
    Planet();
    void draw() override;
    void update() override;
    void loadTexture(const char* filename);

    // Getters
    float getPlanetRadius() const;
    float getOrbitRadius() const;
    float getOrbitSpeed() const;
    float getRotationSpeed() const;
    float getAngle() const;
    float getOrbitAngle() const;
    std::vector<float> getCenter() const;
    std::vector<float> getPlanetColor() const;

    // Setters
    void setPlanetRadius(float radius);
    void setOrbitRadius(float radius);
    void setOrbitSpeed(float speed);
    void setRotationSpeed(float speed);
    void setAngle(float angle);
    void setOrbitAngle(float angle);
    void setCenter(const std::vector<float>& center);
    void setPlanetColor(const std::vector<float>& color);

private:
    float planetRadius;
    float orbitRadius;
    float orbitSpeed;
    float rotationSpeed;
    float angle;
    float orbitAngle;
    GLuint textureID;
    std::vector<float> center;
    std::vector<float> planetColor;
};

#endif // PLANET_H
