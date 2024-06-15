#include "UI_Functions.h"
#include <GL/glut.h>
#include <sstream>
#include <iostream>


void drawText(const char *text, float x, float y, void *font)
{
    glRasterPos2f(x, y);
    for (const char *p = text; *p; p++)
    {
        glutBitmapCharacter(font, *p);
    }
}

void drawStrokedText(const char *text, float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, scale);
    for (const char *p = text; *p; p++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    }
    glPopMatrix();
}

void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawHealthBar(float x, float y, float width, float height, float maxHealth, float currentHealth) {
    // Ensure health value is within the valid range
    if (currentHealth < 0) currentHealth = 0;
    if (currentHealth > maxHealth) currentHealth = maxHealth;

    // Draw background of health bar (full bar)
    glColor3f(0.2f, 0.2f, 0.2f); // Dark gray
    drawRectangle(x, y, width, height);

    // Calculate width of health bar based on current health
    float healthBarWidth = (currentHealth / maxHealth) * width;

    // Draw health bar (red)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawRectangle(x, y, healthBarWidth, height);
}


void decreaseHealth(int& health, int amount)
{
    health -= amount;
    if (health <= 0)
    {
        health = 0;
        exit(0); // Exit the program if health reaches zero
    }
}

void increaseHealth(int& health, int amount)
{
    if (health < 10)
    {
        health += amount;
        if (health > 10)
        {
            health = 10; // Cap health at maximum of 10
        }
    }
}