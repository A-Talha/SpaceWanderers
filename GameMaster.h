#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "GameObject.h"
#include "SpaceShip.h"

enum GameState {
    MAIN_MENU,
    SURVIVAL_MODE,
    TIME_MODE,
    GAME_OVER
};

class GameMaster {
public:
    GameMaster();
    void draw();
    void updateGameState(GameState newState);
    void keyUp();
    void keyDown();
    void keyLeft();
    void keyRight();
    void keySpace();
    void keyChar(unsigned char key);
    void GoToMainMenu();
    void StartSurvivalMode();
    void StartTimeMode();
    void EndGameOver();


private:
    GameState state;
    SpaceShip spaceship;
    int score;
    std::vector<GameObject> gameObjects;
    void DrawMainMenu();
    void DrawSurvivalMode();
    void DrawTimeMode();
    void DrawGameOver();

};

#endif