#ifndef FIREBULLET_H
#define FIREBULLET_H

#include "GameObject.h"

class FireBullet : public GameObject {
public:
    // Constructor
    FireBullet(int firePower, std::vector<float> position, std::vector<float> lookAt);

    // Additional methods specific to FireBullet
    // void adjustVertices();
    // std::vector<float> calculateVertices(float radius);
    void update() override;
    void draw() override;

private:
    // Additional attributes specific to FireBullet
    float moveSpeed;
    float direction[3];
    int firePower;
};

#endif