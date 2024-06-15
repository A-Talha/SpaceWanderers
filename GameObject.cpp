#include "GameObject.h"
#include "GameMaster.h"
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>

GameObject::GameObject(ObjectType type) : type(type), texture(0), shader(0) {
    setPosition(0.0f, 0.0f, 0.0f);
    setRotation(0.0f, 0.0f, 1.0f, 0.0f);
    setScale(1.0f, 1.0f, 1.0f);
}
 
void GameObject::setPosition(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

void GameObject::setRotation(float angle, float x, float y, float z) {
    rotation[0] = angle;
    rotation[1] = x;
    rotation[2] = y;
    rotation[3] = z;
}

void GameObject::setScale(float x, float y, float z) {
    scale[0] = x;
    scale[1] = y;
    scale[2] = z;
}

void GameObject::setVertices(const std::vector<float>& verts) {
    vertices = verts;
}

void GameObject::setColors(const std::vector<float>& cols) {
    colors = cols;
}

void GameObject::setTexture(GLuint tex) {
    texture = tex;
}

void GameObject::setShader(GLuint sh) {
    shader = sh;
}

void GameObject::applyTransformations() {
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(rotation[0], rotation[1], rotation[2], rotation[3]);
    glScalef(scale[0], scale[1], scale[2]);
}

void GameObject::draw(){
    glPushMatrix();
    applyTransformations();

    if (shader) {
        glUseProgram(shader);
    }

    if (texture) {
        glBindTexture(GL_TEXTURE_3D, texture);
        glEnable(GL_TEXTURE_3D);
    }

    glBegin(GL_QUADS);
    for (size_t i = 0; i < vertices.size(); i += 3) {
        glColor3f(colors[i*3], colors[i*3+1], colors[i*3+2]);
        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
    glEnd();
    

    if (texture) {
        glDisable(GL_TEXTURE_2D);
    }

    if (shader) {
        glUseProgram(0);
    }

    glPopMatrix();
}

float GameObject::getPositionX() {
    return position[0];
}

float GameObject::getPositionY() {
    return position[1];
}

float GameObject::getPositionZ() {
    return position[2];
}

float* GameObject::getPosition() {
    return position;
}

float GameObject::getRotationAngle() {
    return rotation[0];
}

float GameObject::getRotationX() {
    return rotation[1];
}

float GameObject::getRotationY() {
    return rotation[2];
}

float GameObject::getRotationZ() {
    return rotation[3];
}

float GameObject::getScaleX() {
    return scale[0];
}

float GameObject::getScaleY() {
    return scale[1];
}

float GameObject::getScaleZ() {
    return scale[2];
}

std::vector<float> GameObject::getVertices() {
    return vertices;
}

std::vector<float> GameObject::getColors() {
    return colors;
}

std::vector<float> GameObject::getVerticesTranformed() {
    // Create a deep copy of vertices
    std::vector<float> transformedVertices = vertices;

    // Scaling
    for (size_t i = 0; i < transformedVertices.size(); i += 3) {
        transformedVertices[i] *= scale[0];
        transformedVertices[i + 1] *= scale[1];
        transformedVertices[i + 2] *= scale[2];
    }

    // Rotation around the y-axis
    float angleRad = rotation[0] * (3.14159265f / 180.0f);
    float cosAngle = cos(angleRad);
    float sinAngle = sin(angleRad);

    for (size_t i = 0; i < transformedVertices.size(); i += 3) {
        float x = transformedVertices[i];
        float z = transformedVertices[i + 2];

        transformedVertices[i] = x * cosAngle + z * sinAngle;
        transformedVertices[i + 2] = -x * sinAngle + z * cosAngle;
    }

    // Translation
    for (size_t i = 0; i < transformedVertices.size(); i += 3) {
        transformedVertices[i] += position[0];
        transformedVertices[i + 1] += position[1];
        transformedVertices[i + 2] += position[2];
    }

    return transformedVertices;
}

ObjectType GameObject::getType() {
    return type;
}

void GameObject::checkCollision(GameObject* other) {
    const float * otherPos = other -> getPosition();
    float distance = sqrt(pow(position[0] - otherPos[0], 2) + pow(position[1] - otherPos[1], 2) + pow(position[2] - otherPos[2], 2));

    if(distance < other -> bounding_sphere_radius + bounding_sphere_radius){
        // new collision
        for(GameObject* collision : collisions){
            if(collision == other){
                onCollisionPersist(other);
                other -> onCollisionPersist(this);
                return;
            }
        }
        onCollisionEnter(other);
        other -> onCollisionEnter(this);

        collisions.push_back(other);
    }
    else{
        for(int i = 0; i < collisions.size(); i++){
            if(collisions[i] == other){
                onCollisionExit(other);
                other -> onCollisionExit(this);
                collisions.erase(collisions.begin() + i);
                collisions.shrink_to_fit();
                break;
            }
        }
    }
}

void GameObject::Destroy(GameObject *object)
{
    GameMaster::GetInstance().DestroyGameObject(object);
}

//empty update function
void GameObject::update() {
    // Do nothing by default
}

//empty update function
void GameObject::update(float playerPosition[3]) {
    // Do nothing by default
}