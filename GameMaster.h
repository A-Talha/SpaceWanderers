#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "GameObject.h"
#include "SpaceShip.h"
#include "Planet.h"

enum GameState {
    MAIN_MENU,
    SURVIVAL_MODE,
    TIME_MODE,
    GAME_OVER
};

class GameMaster {
public:
    GameMaster();
    ~GameMaster();
    void draw();
    void updateGameState(GameState newState);
    void SpecialKey(int key, int x, int y);
    void keyChar(unsigned char key);
    void GoToMainMenu();
    void StartSurvivalMode();
    void StartTimeMode();
    void EndGameOver();
    void Update();

private:
    GameState state;
    SpaceShip spaceship;
    Planet sun;
    std::vector<float> SUN_POSITION = {0.0f, 1000.0f, 0.0f, 1.0f}; // x, y, z, w
    std::vector<float> SUN_COLOR = {1.0f, 1.0f, 0.8f, 1.0f}; // White-yellow light
    int score;
    const int WINDOW_WIDTH = 1300;
    const int WINDOW_HEIGHT = 800;
    std::vector<GameObject*> gameObjects;
    void DrawMainMenu();
    void DrawSurvivalMode();
    void DrawTimeMode();
    void DrawGameOver();
    void DrawScene();
    void clearGameObjects();
};

#endif
