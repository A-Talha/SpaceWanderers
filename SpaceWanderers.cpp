#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "GameObject.h"
#include "SpaceShip.h"

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float MAP_SIZE = 10000.0f;

// Sun position
const float SUN_POSITION[] = {0.0f, 1000.0f, 0.0f, 1.0f}; // x, y, z, w
const float SUN_COLOR[] = {1.0f, 1.0f, 0.8f, 1.0f}; // White-yellow light

// Spaceship object
SpaceShip spaceship;

// Function to initialize OpenGL settings
void initOpenGL() {
    // Set the background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set the light properties
    glLightfv(GL_LIGHT0, GL_POSITION, SUN_POSITION);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, SUN_COLOR);
    glLightfv(GL_LIGHT0, GL_SPECULAR, SUN_COLOR);

    // Set global ambient light
    GLfloat globalAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Initialize spaceship properties
    spaceship.setPosition(0.0f, 1000.0f, 2000.0f);
    spaceship.setScale(1.0f, 1.0f, 1.0f);

    // Define spaceship vertices (simple triangle)
    std::vector<float> spaceshipVertices = {
        0.0f, 100.0f, 0.0f,
        -100.0f, -100.0f, 100.0f,
        100.0f, -100.0f, 100.0f,
        0.0f, 100.0f, 0.0f,
        100.0f, -100.0f, 100.0f,
        100.0f, -100.0f, -100.0f,
        0.0f, 100.0f, 0.0f,
        100.0f, -100.0f, -100.0f,
        -100.0f, -100.0f, -100.0f,
        0.0f, 100.0f, 0.0f,
        -100.0f, -100.0f, -100.0f,
        -100.0f, -100.0f, 100.0f
    };
    std::vector<float> colors;
    for (int i = 0; i < spaceshipVertices.size(); i++) {
        colors.push_back(0);
        colors.push_back(0.9);
        colors.push_back(0.9);
    }

    spaceship.setVertices(spaceshipVertices);
    spaceship.setColors(colors);
}

// Function to handle rendering the scene
void display() {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the view matrix
    glLoadIdentity();
    // Set the camera position, look at point, and up vector as a first-person camera from the spaceship
    gluLookAt(0.0, 2000.0, 6000.0, // Camera position
              0.0, 0.0, 0.0,       // Look at point
              0.0, 1.0, 0.0);      // Up vector

    // Draw the sun
    glPushMatrix();
    glTranslatef(SUN_POSITION[0], SUN_POSITION[1], SUN_POSITION[2]);
    glColor3f(SUN_COLOR[0], SUN_COLOR[1], SUN_COLOR[2]);
    glutSolidSphere(500.0, 20, 20); // Sun with a radius of 500
    glPopMatrix();

    // Draw the spaceship
    spaceship.draw();

    // Swap the front and back buffers to display the scene
    glutSwapBuffers();
}

// Function to handle window resizing
void reshape(int width, int height) {
    // Set the viewport to cover the new window size
    glViewport(0, 0, width, height);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 20000.0);

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
        case 'z':
            spaceship.RotateLeft();
            break;
        case 'x':
            spaceship.RotateRight();
            break;
        // Add more key controls here for your game
    }
    glutPostRedisplay();
}

// Function to handle special key input (arrow keys)
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            spaceship.moveForward();
            break;
        case GLUT_KEY_DOWN:
            spaceship.moveBackward();
            break;
        case GLUT_KEY_LEFT:
            spaceship.moveLeft();
            break;
        case GLUT_KEY_RIGHT:
            spaceship.moveRight();
            break;
    }
    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // Create the window
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Space Wanderers");

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing GLEW!" << std::endl;
        return -1;
    }

    // Initialize OpenGL settings
    initOpenGL();

    // Set up callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    // Start the main loop
    glutMainLoop();

    return 0;
}
