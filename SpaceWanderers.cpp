#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "GameMaster.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <windows.h>

// Window dimensions
const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 800;
const float MAP_SIZE = 10000.0f;

int g_hWnd;
HGLRC g_hRC;
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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Initialize GLUT
    glutInit(&__argc, __argv); // Pass command line arguments to GLUT initialization
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

    // Set up OpenGL context
    g_hRC = wglGetCurrentContext();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set up callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);

    // Start the main loop
    glutMainLoop();

    // Quit SDL
    SDL_Quit();

    return 0;
}
