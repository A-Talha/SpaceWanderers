#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <windows.h>

// Global variables for the window handle and OpenGL rendering context
int g_hWnd;
HGLRC g_hRC;

// Forward declarations
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void playSound(const std::string &filename);
void display();
void handleKeypress(unsigned char key, int x, int y);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Initialize GLUT
    glutInit(&__argc, __argv); // Pass command line arguments to GLUT initialization
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    g_hWnd = glutCreateWindow("OpenGL with SDL2 Sound");

    // Initialize GLEW
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        std::cerr << "Error initializing GLEW: " << glewGetErrorString(glewStatus) << std::endl;
        return 1;
    }

    // Set up OpenGL context
    g_hRC = wglGetCurrentContext();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set up GLUT callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();

    // Quit SDL
    SDL_Quit();

    return 0;
}

void playSound(const std::string &filename)
{
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    // Load sound
    Mix_Chunk *Sound = Mix_LoadWAV(filename.c_str());
    if (Sound == nullptr)
    {
        std::cerr << "Failed to load crash sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    // Play sound
    Mix_PlayChannel(-1, Sound, 0);

    // Wait for sound to finish
    SDL_Delay(1000);

    // Clean up
    Mix_FreeChunk(Sound);
    Mix_CloseAudio();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Your OpenGL rendering code here

    glutSwapBuffers();
}

void handleKeypress(unsigned char key, int x, int y)
{
    if (key == 's')
    {
        playSound("D:\\Study\\Semester 6\\Graphics\\Project\\Submitted\\SpaceWanderers\\Explosion.wav");
    }
    else if (key == 'l')
    {
        playSound("D:\\Study\\Semester 6\\Graphics\\Project\\Submitted\\SpaceWanderers\\Laser.wav");
    }
}