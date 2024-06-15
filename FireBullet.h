#ifndef FIREBULLET_H
#define FIREBULLET_H

#include "GameObject.h"

class FireBullet : public GameObject {
public:
    // Constructor
    FireBullet(int firePower, std::vector<float> position, std::vector<float> lookAt, std::vector<GameObject*>& objectsRef);

    // Additional methods specific to FireBullet
    // void adjustVertices();
    // std::vector<float> calculateVertices(float radius);
    void update() override;
    void draw() override;

private:
    // Additional attributes specific to FireBullet
    std::vector<GameObject*>& gameObjectsRef;
    float moveSpeed;
    float direction[3];
    float initialPosition[3];
    int firePower;
    int cnt = 0;
};

#endif