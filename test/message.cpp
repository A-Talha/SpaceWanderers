#include <GL/glut.h>
#include <iostream>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

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

void drawRectangle(float x, float y, float width, float height)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the title
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawStrokedText("Space Wanderers", 250.0f, 450.0f, 0.3f);

    // Draw the menu options with background rectangles
    glColor3f(0.0f, 0.0f, 0.8f);                  // Blue color
    drawRectangle(300.0f, 280.0f, 200.0f, 30.0f); // Survival Mode button
    drawRectangle(300.0f, 230.0f, 200.0f, 30.0f); // Time Attack Mode button
    drawRectangle(300.0f, 180.0f, 200.0f, 30.0f); // Exit button

    glColor3f(1.0f, 1.0f, 1.0f); // White color for text
    drawText("1. Survival Mode", 320.0f, 290.0f, GLUT_BITMAP_HELVETICA_18);
    drawText("2. Time Attack Mode", 320.0f, 240.0f, GLUT_BITMAP_HELVETICA_18);
    drawText("3. Exit", 320.0f, 190.0f, GLUT_BITMAP_HELVETICA_18);

    glFlush();
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT); // Set the orthographic view
    glMatrixMode(GL_MODELVIEW);
}

void processMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convert window coordinates to OpenGL coordinates
        int oglY = WINDOW_HEIGHT - y;

        // Check if the click is within the "Survival Mode" option area
        if (x >= 300 && x <= 500 && oglY >= 280 && oglY <= 310)
        {
            cout << "Survival Mode clicked!" << endl;
        }
        // Check if the click is within the "Time Attack Mode" option area
        else if (x >= 300 && x <= 500 && oglY >= 230 && oglY <= 260)
        {
            cout << "Time Attack Mode clicked!" << endl;
        }
        // Check if the click is within the "Exit" option area
        else if (x >= 300 && x <= 500 && oglY >= 180 && oglY <= 210)
        {
            cout << "Exit clicked!" << endl;
            exit(0);
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Space Wanderers");
    glutDisplayFunc(display);
    glutMouseFunc(processMouse);
    init();

    cout << "Initialization complete" << endl; // Debugging message

    glutMainLoop();

    cout << "Exiting program" << endl; // Debugging message
    return 0;
}
