#define GLUT_DISABLE_ATEXIT_HACK
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
#include "EnemyShip.h"
#include "UI_Functions.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <thread>
#include <windows.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;

enum GameState {
    MAIN_MENU,
    SURVIVAL_MODE,
    TIME_MODE,
    GAME_OVER
};

enum GameResult {
    WIN,
    LOSE,
    TIMEISUP
};

class GameMaster {
public:
    static GameMaster& GetInstance() {
        static GameMaster instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    // Delete the copy constructor and assignment operator to prevent copying
    GameMaster(const GameMaster&) = delete;
    GameMaster& operator=(const GameMaster&) = delete;
    
    void playSound(const std::string &filename);
    void draw();
    void updateGameState(GameState newState);
    void processMouse(int button, int state, int x, int y);
    void keyPressed(int key, bool pressed);
    void handleKeys();
    void SpecialKey(int key, int x, int y);
    void SpecialKeyUp(int key, int x, int y);
    void keyChar(unsigned char key);
    void keyUp(unsigned char key);
    void GoToMainMenu();
    void StartSurvivalMode();
    void StartTimeMode();
    void EndGameOver(GameResult result);
    void Update();
    void DestroyGameObject(GameObject* gameObject);

private:
    GameMaster();
    ~GameMaster();
    GameState state;
    GameResult result;
    SpaceShip spaceship;
    std::vector<float> SUN_POSITION = {0.0f, 1000.0f, 0.0f, 1.0f}; // x, y, z, w
    std::vector<float> SUN_COLOR = {1.0f, 0.5f, 0.0f, 1.0f}; // White-yellow light
    std::unordered_set<int> keysPressed;
    const int WINDOW_WIDTH = 1300;
    const int WINDOW_HEIGHT = 800;
    int score;
    int currentID;
    int maxNumberOfEnemies;
    int maxNumberOfEnemiesToSpawned;
    int CurrentNumberOfEnemies;
    int CurrentNumberOfEnemiesKilled;
    float startTime;
    float currentTime;
    float TimeLimit;
    float lastTimeEnemySpawned;
    float intervalTimeToSpawnEnemy;
    std::vector<float> colors;
    std::vector<float> enemyColors;
    std::vector<GameObject*> gameObjects;
    std::vector<EnemyShip*> enemyShips;
    std::vector<Planet*> planets;
    void DrawMainMenu();
    void DrawSurvivalMode();
    void DrawTimeMode();
    void DrawGameOver();
    void DrawScene();
    void addPlanets();
    void clearGameObjects();
    void createEnemyShip(int id,std::vector<float> Vertices, std::vector<float> Colors);
    void checkSpaceShipwithinBoundaries();
    void IncreaseScore(int amount);
    void increaseHealth(int amount);
    void decreaseHealth(int amount);
    bool initAudio();
    void closeAudio();
    std::unordered_map<std::string, Mix_Chunk*> soundCache;
};

#endif
