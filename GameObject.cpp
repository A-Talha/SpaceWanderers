#include "GameObject.h"
#include <GL/freeglut.h>

GameObject::GameObject(ObjectType type) : type(type), texture(0), shader(0) {
    setPosition(0.0f, 0.0f, 0.0f);
    setRotation(0.0f, 0.0f, 0.0f, 1.0f);
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

void GameObject::draw() {
    glPushMatrix();
    applyTransformations();

    if (shader) {
        glUseProgram(shader);
    }

    if (texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_TEXTURE_2D);
    }

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < vertices.size(); i += 3) {
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
