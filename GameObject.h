#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <GL/glew.h>

enum ObjectType {
    PLANET,
    SPACESHIP,
    ENEMYSHIP,
    OTHER
};

class GameObject {
public:
    // Constructors
    GameObject(ObjectType type);

    virtual void draw();
    virtual void update();
    virtual void update(float playerPosition[3]);
    

    // Public member functions
    void setPosition(float x, float y, float z);
    void setRotation(float angle, float x, float y, float z);
    void setScale(float x, float y, float z);
    void setVertices(const std::vector<float>& vertices);
    void setColors(const std::vector<float>& cols);
    void setTexture(GLuint texture);
    void setShader(GLuint shader);
    void setCenter(float x, float y, float z);

    //getters
    float getPositionX();
    float getPositionY();
    float getPositionZ();
    float getRotationAngle();
    float getRotationX();
    float getRotationY();
    float getRotationZ();
    float getScaleX();
    float getScaleY();
    float getScaleZ();
    //get type
    ObjectType getType();
    std::vector<float> getVertices();
    std::vector<float> getVerticesTranformed();


private:
    // Private member variables
    ObjectType type;
    float position[3];
    float rotation[4];
    float scale[3];
    std::vector<float> vertices;
    std::vector<float> colors;
    GLuint texture;
    GLuint shader;

    // Private member functions
    void applyTransformations();
};

#endif
