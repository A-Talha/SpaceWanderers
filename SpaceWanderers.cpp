#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "GameMaster.h"


// Window dimensions
const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 800;
const float MAP_SIZE = 10000.0f;

//GameMaster object
GameMaster gameMaster;

void Update() {
    gameMaster.Update();
    glutPostRedisplay();
}

// Function to initialize OpenGL settings
void initOpenGL() {
    gameMaster.GoToMainMenu();

    glutIdleFunc(Update);
}



// Function to handle rendering the scene
void display() {
    gameMaster.draw();
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
    gameMaster.keyChar(key);
    glutPostRedisplay();
}

// Function to handle special key input (arrow keys)
void specialKeys(int key, int x, int y) {
    gameMaster.SpecialKey(key, x, y);
    glutPostRedisplay();
}

// Function to handle mouse input
void mouse(int button, int state, int x, int y) {
    gameMaster.processMouse(button, state, x, y);
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
    glutMouseFunc(mouse);

    // Start the main loop
    glutMainLoop();

    return 0;
}
