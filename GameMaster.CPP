#include "GameMaster.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>


GameMaster::GameMaster() {
    state = MAIN_MENU; // Initial game state
    if (!initAudio())
        std::cerr << "Failed to initialize audio system!" << std::endl;
}

GameMaster::~GameMaster() {
    clearGameObjects();
    closeAudio();
}

void GameMaster::DestroyGameObject(GameObject* gameObject) {
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
        if (*it == gameObject) {
            gameObjects.erase(it);
            break;
        }
    }
    std::cout << "Destroying game object..." << std::endl;
    // Delete the object from memory
    // delete gameObject;
    if(gameObject -> getType() == ObjectType::SPACESHIP){
        EndGameOver(WIN);
    }
}
bool GameMaster::initAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void GameMaster::closeAudio() {
    for (auto &pair : soundCache) {
        Mix_FreeChunk(pair.second);
    }
    soundCache.clear();
    Mix_CloseAudio();
}

void GameMaster::playSound(const std::string &filename) {
    Mix_Chunk *sound = nullptr;

    auto it = soundCache.find(filename);
    if (it != soundCache.end()) {
        sound = it->second;
    } else {
        sound = Mix_LoadWAV(filename.c_str());
        if (sound == nullptr) {
            std::cerr << "Failed to load sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return;
        }
        soundCache[filename] = sound;
    }

    if (Mix_PlayChannel(-1, sound, 0) == -1) {
        std::cerr << "Unable to play sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void GameMaster::clearGameObjects() {
    std::cout << "Clearing game objects..." << std::endl;
    for (GameObject* obj : gameObjects) {
        obj = nullptr;
    }
    gameObjects.clear();
    for (EnemyShip* enemy : enemyShips) {
        enemy = nullptr;
    }
    enemyShips.clear();
    for (Planet* planet : planets) {
        planet = nullptr;
    }
    planets.clear();
    std::cout << "Game objects cleared." << std::endl;
}

void GameMaster::draw() {
    switch (state) {
    case MAIN_MENU:
        DrawMainMenu();
        break;
    case SURVIVAL_MODE:
        DrawSurvivalMode();
        break;
    case TIME_MODE:
        DrawTimeMode();
        break;
    case GAME_OVER:
        DrawGameOver();
        break;
    }
}

void GameMaster::updateGameState(GameState newState) {
    std::cout << "Updating game state from " << state << " to " << newState << std::endl;
    state = newState;
    glutPostRedisplay();
}

void GameMaster::processMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && GameMaster::state == MAIN_MENU) {
        // Convert window coordinates to OpenGL coordinates
        int oglY = WINDOW_HEIGHT - y;

        // Check if the click is within the "Survival Mode" option area
        if (x >= 300 && x <= 500 && oglY >= 280 && oglY <= 310) {
            std::cout << "Survival Mode clicked!" << std::endl;
            StartSurvivalMode();
        }
        // Check if the click is within the "Time Attack Mode" option area
        else if (x >= 300 && x <= 500 && oglY >= 230 && oglY <= 260) {
            std::cout << "Time Attack Mode clicked!" << std::endl;
            StartTimeMode();
        }
        // Check if the click is within the "Exit" option area
        else if (x >= 300 && x <= 500 && oglY >= 180 && oglY <= 210) {
            std::cout << "Exit clicked!" << std::endl;
            clearGameObjects();
            exit(0);
        }
    }
}

 void GameMaster::keyPressed(int key, bool pressed) {
    if (pressed) {
        keysPressed.insert(key);
    } else {
        keysPressed.erase(key);
    }

    handleKeys();
}

void GameMaster::handleKeys() {
    for (int key : keysPressed) {
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
            case 27: // ESC key
                if(state == MAIN_MENU){
                    clearGameObjects();
                    exit(0);
                } else {
                    std::cout << "Going to main menu..." << std::endl;
                    GoToMainMenu();
                }
                break;
            case 'z':
                spaceship.RotateLeft();
                break;
            case 'x':
                spaceship.RotateRight();
                break;
            case ' ':
                std::thread(&GameMaster::playSound, this, "src/Laser.wav").detach();
                spaceship.fireWeapon(gameObjects);
                break;
            case 'w':
                increaseHealth(10);
                break;
            case 's':
                decreaseHealth(10);
                break;
            case 'c':
                std::thread(&GameMaster::playSound, this, "src/Explosion.wav").detach();
                break;
            case 'v':
                std::thread(&GameMaster::playSound, this, "src/Laser.wav").detach();
                break;
            // Add more cases as needed
        }
    }

    // Update views after handling all keys
    spaceship.updateFirstPersonView();
    spaceship.updateThirdPersonView();
    glutPostRedisplay(); // Ensure screen refresh after key handling
}

void GameMaster::SpecialKey(int key, int x, int y) {
    std::cout << "Key pressed: " << key << std::endl;
    keyPressed(key, true); // Assuming GLUT_DOWN event
}

void GameMaster::keyChar(unsigned char key) {
    keyPressed(key, true); // Assuming key press event
}

void GameMaster::keyUp(unsigned char key) {
    keyPressed(key, false); // Assuming key release event
}

void GameMaster::SpecialKeyUp(int key, int x, int y) {
    keyPressed(key, false); // Assuming GLUT_UP event
}

void GameMaster::GoToMainMenu() {
    std::cout << "Clearing game objects before going to main menu..." << std::endl;
    clearGameObjects();

    // Reset OpenGL state
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_SCISSOR_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    updateGameState(MAIN_MENU);
}


void GameMaster::StartSurvivalMode() {
    std::cout << "Starting Survival Mode..." << std::endl;
    
    // Set the viewport to cover the new window size
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 20000.0);

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const float SUN_POSITION1[] = {0.0f, 2500.0f, 0.0f, 1.0f}; // x, y, z, w
    const float SUN_COLOR1[] = {1.0f, 1.0f, 0.8f, 1.0f}; // White-yellow light

    // Clear any existing game objects
    clearGameObjects();

    addPlanets();

    // Set the background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set the light properties
    glLightfv(GL_LIGHT0, GL_POSITION, SUN_POSITION1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, SUN_COLOR1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, SUN_COLOR1);

    // Set global ambient light
    GLfloat globalAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Initialize spaceship properties
    spaceship = SpaceShip();
    spaceship.setPosition(0.0f, 1000.0f, 2000.0f);
    spaceship.setScale(1.0f, 1.0f, 1.0f);

    std::vector<float> spaceshipVertices = {
        -200.0f,75.0f,-400.0f,
        -200.0f,-75.0f,-400.0f,
        200.0f,-75.0f,-400.0f,
        200.0f,75.0f,-400.0f,
        200.0f,-75.0f,-400.0f,
        200.0f,75.0f,-400.0f,
        200.0f,75.0f,400.0f,
        200.0f,-75.0f,400.0f,
        200.0f,75.0f,400.0f,
        200.0f,-75.0f,400.0f,
        -200.0f,-75.0f,400.0f,
        -200.0f,75.0f,400.0f,
        -200.0f,-75.0f,400.0f,
        -200.0f,75.0f,400.0f,
        -200.0f,75.0f,-400.0f,
        -200.0f,-75.0f,-400.0f,
        -200.0f,75.0f,-400.0f,
        200.0f,75.0f,-400.0f,
        200.0f,75.0f,400.0f,
        -200.0f,75.0f,400.0f,
        -200.0f,-75.0f,-400.0f,
        200.0f,-75.0f,-400.0f,
        200.0f,-75.0f,400.0f,
        -200.0f,-75.0f,400.0f
    };

    for (int i = 0; i < spaceshipVertices.size(); i++) {
        colors.push_back(0);
        colors.push_back(0.9);
        colors.push_back(0.9);
    }

    for (int i = 0; i < spaceshipVertices.size(); i++) {
        enemyColors.push_back(0.9);
        enemyColors.push_back(0);
        enemyColors.push_back(0);
    }

    spaceship.setVertices(spaceshipVertices);
    spaceship.setColors(colors);
    spaceship.setHealth(100);
    spaceship.setWeaponPower(20);
    spaceship.updateFirstPersonView();
    spaceship.updateThirdPersonView();

    gameObjects.push_back(&spaceship);

    createEnemyShip(0, spaceshipVertices, enemyColors);

    updateGameState(SURVIVAL_MODE);
    // Set the initial score to 0
    score = 0;
    CurrentNumberOfEnemiesKilled = 0;
    // Set the current ID to 1
    currentID = 1;
    // Set the maximum number of enemies to 5
    maxNumberOfEnemies = 5;
    // Set the current number of enemies to 1
    CurrentNumberOfEnemies = 1;
    // Set the start time to the current time
    startTime = glutGet(GLUT_ELAPSED_TIME);
    // Set the current time to the start time
    currentTime = startTime;
    // Set the time interval to spawn an enemy to 5 seconds
    intervalTimeToSpawnEnemy = 7000;
    // Set the last time an enemy was spawned to the start time
    lastTimeEnemySpawned = startTime;


    std::cout << "Survival Mode started." << std::endl;
}


void GameMaster::StartTimeMode() {
    std::cout << "Starting Time Attack Mode..." << std::endl;
    

    const float SUN_POSITION1[] = {0.0f, 2500.0f, 0.0f, 1.0f}; // x, y, z, w
    const float SUN_COLOR1[] = {1.0f, 1.0f, 0.8f, 1.0f}; // White-yellow light

    // Clear any existing game objects
    clearGameObjects();

    addPlanets();

    // Set the background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set the light properties
    glLightfv(GL_LIGHT0, GL_POSITION, SUN_POSITION1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, SUN_COLOR1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, SUN_COLOR1);

    // Set global ambient light
    GLfloat globalAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Initialize spaceship properties
    spaceship = SpaceShip();
    spaceship.setPosition(0.0f, 1000.0f, 2000.0f);
    spaceship.setScale(1.0f, 1.0f, 1.0f);

    std::vector<float> spaceshipVertices = {
        -200.0f,75.0f,-400.0f,
        -200.0f,-75.0f,-400.0f,
        200.0f,-75.0f,-400.0f,
        200.0f,75.0f,-400.0f,
        200.0f,-75.0f,-400.0f,
        200.0f,75.0f,-400.0f,
        200.0f,75.0f,400.0f,
        200.0f,-75.0f,400.0f,
        200.0f,75.0f,400.0f,
        200.0f,-75.0f,400.0f,
        -200.0f,-75.0f,400.0f,
        -200.0f,75.0f,400.0f,
        -200.0f,-75.0f,400.0f,
        -200.0f,75.0f,400.0f,
        -200.0f,75.0f,-400.0f,
        -200.0f,-75.0f,-400.0f,
        -200.0f,75.0f,-400.0f,
        200.0f,75.0f,-400.0f,
        200.0f,75.0f,400.0f,
        -200.0f,75.0f,400.0f,
        -200.0f,-75.0f,-400.0f,
        200.0f,-75.0f,-400.0f,
        200.0f,-75.0f,400.0f,
        -200.0f,-75.0f,400.0f
    };

    for (int i = 0; i < spaceshipVertices.size(); i++) {
        colors.push_back(0);
        colors.push_back(0.9);
        colors.push_back(0.9);
    }

    for (int i = 0; i < spaceshipVertices.size(); i++) {
        enemyColors.push_back(0.9);
        enemyColors.push_back(0);
        enemyColors.push_back(0);
    }

    spaceship.setVertices(spaceshipVertices);
    spaceship.setColors(colors);
    spaceship.setHealth(100);
    spaceship.setWeaponPower(20);
    spaceship.updateFirstPersonView();
    spaceship.updateThirdPersonView();

    gameObjects.push_back(&spaceship);

    // Set initial game parameters
    score = 0;
    CurrentNumberOfEnemiesKilled = 0;
    currentID = 1;
    maxNumberOfEnemies = 3;
    CurrentNumberOfEnemies = 0;
    maxNumberOfEnemiesToSpawned = 15;
    startTime = glutGet(GLUT_ELAPSED_TIME);
    currentTime = startTime;
    TimeLimit = 300000;
    intervalTimeToSpawnEnemy = 5000;
    lastTimeEnemySpawned = startTime;

    updateGameState(TIME_MODE);
}


void GameMaster::EndGameOver(GameResult result) {
    std::cout << "Game Over!" << std::endl;
    this->result = result;
    clearGameObjects();

    // Reset OpenGL state
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_SCISSOR_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    updateGameState(GAME_OVER);
    glutPostRedisplay();
}

void GameMaster::DrawMainMenu() {
    
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset the viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Reset the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);

    // Reset the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Reset color
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the title
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawStrokedText("Space Wanderers", 250.0f, 450.0f, 0.3f);

    // Draw the menu options with background rectangles
    glColor3f(0.0f, 0.0f, 0.8f);                  // Blue color
    drawRectangle(300.0f, 280.0f, 200.0f, 30.0f); // Survival Mode button
    drawRectangle(300.0f, 230.0f, 200.0f, 30.0f); // Time Attack Mode button
    drawRectangle(300.0f, 180.0f, 200.0f, 30.0f); // Exit button

    // Set color for text
    glColor3f(1.0f, 1.0f, 1.0f); // White color for text
    drawText("1. Survival Mode", 320.0f, 290.0f, GLUT_BITMAP_HELVETICA_18);
    drawText("2. Time Attack Mode", 320.0f, 240.0f, GLUT_BITMAP_HELVETICA_18);
    drawText("3. Exit", 320.0f, 190.0f, GLUT_BITMAP_HELVETICA_18);

    // Swap buffers
    glutSwapBuffers();

}


void GameMaster::DrawSurvivalMode() {
    // Clear the color and depth buffers for the main viewport
    // Set the viewport to cover the new window size
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 20000.0);

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // First viewport (main view)
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glLoadIdentity();
    // Set the first-person camera from the spaceship
    std::vector<float> cameraPosition1 = spaceship.getFirstPersonCameraPosition();
    std::vector<float> lookAt1 = spaceship.getFirstPersonLookAt();
    gluLookAt(cameraPosition1[0], cameraPosition1[1], cameraPosition1[2], 
              lookAt1[0], lookAt1[1], lookAt1[2], 
              0.0f, 1.0f, 0.0f);

    // Draw the scene
    DrawScene();

    // Second viewport (alternative view)
    int smallViewportWidth = WINDOW_WIDTH * 11 / 40;
    int smallViewportHeight = WINDOW_HEIGHT * 11 / 40;
    int smallViewportX = WINDOW_WIDTH - smallViewportWidth;
    int smallViewportY = 0;

    // Enable scissor test to limit the clearing to the second viewport
    glEnable(GL_SCISSOR_TEST);
    glScissor(smallViewportX, smallViewportY, smallViewportWidth, smallViewportHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    glViewport(smallViewportX, smallViewportY, smallViewportWidth, smallViewportHeight);
    glLoadIdentity();
    std::vector<float> cameraPosition2 = spaceship.getThirdPersonCameraPosition();
    std::vector<float> lookAt2 = spaceship.getThirdPersonLookAt();
    gluLookAt(cameraPosition2[0], cameraPosition2[1], cameraPosition2[2], 
              lookAt2[0], lookAt2[1], lookAt2[2], 
              0.0f, 1.0f, 0.0f);

    // Draw the scene again
    DrawScene();

    // Create a viewport for the top middle corner of the screen
    int topViewportWidth = WINDOW_WIDTH * 3 / 4;
    int topViewportHeight = WINDOW_HEIGHT * 1 / 10;
    int topViewportX = WINDOW_WIDTH * 1 / 8;
    int topViewportY = WINDOW_HEIGHT - topViewportHeight;

    // Enable scissor test to limit the clearing to the third viewport
    glEnable(GL_SCISSOR_TEST);
    glScissor(topViewportX, topViewportY, topViewportWidth, topViewportHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // Set up orthographic projection for the top viewport
    glViewport(topViewportX, topViewportY, topViewportWidth, topViewportHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, topViewportWidth, 0.0, topViewportHeight);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Create and draw the health bar
    //disable depth test
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);
    // draw the score on the top left of the viewport
    glColor3f(1.0f, 1.0f, 1.0f);
    std::string scorestring = "Score: " + std::to_string(score);
    drawText(scorestring.c_str(), 0, 30.0f, GLUT_BITMAP_HELVETICA_18);
    // draw the time elapsed on the top right of the viewport
    float timeElapsed = (currentTime - startTime) / 1000;
    std::string timeString = "Time Elapsed: " + std::to_string(timeElapsed);
    std::string enemiesRemaining = "Enemies Remaining: " + std::to_string(max(CurrentNumberOfEnemies,maxNumberOfEnemiesToSpawned));
    drawText(enemiesRemaining.c_str(), 200, 30.0f, GLUT_BITMAP_HELVETICA_18);
    //number of enemies killed
    std::string enemiesKilled = "Enemies Killed: " + std::to_string(CurrentNumberOfEnemiesKilled);
    drawText(enemiesKilled.c_str(), 200, 50.0f, GLUT_BITMAP_HELVETICA_18);
    drawText(timeString.c_str(), 0 , 50.0f, GLUT_BITMAP_HELVETICA_18);
    drawHealthBar(0, 0, topViewportWidth, 20.0, 100.0, spaceship.getHealth());
    //enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);


    // Swap the front and back buffers to display the scene
    glutSwapBuffers();
}

void GameMaster::DrawTimeMode() {
    // Clear the color and depth buffers for the main viewport
    // Set the viewport to cover the new window size
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 20000.0);

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // First viewport (main view)
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glLoadIdentity();
    // Set the first-person camera from the spaceship
    std::vector<float> cameraPosition1 = spaceship.getFirstPersonCameraPosition();
    std::vector<float> lookAt1 = spaceship.getFirstPersonLookAt();
    gluLookAt(cameraPosition1[0], cameraPosition1[1], cameraPosition1[2], 
              lookAt1[0], lookAt1[1], lookAt1[2], 
              0.0f, 1.0f, 0.0f);

    // Draw the scene
    DrawScene();

    // Second viewport (alternative view)
    int smallViewportWidth = WINDOW_WIDTH * 11 / 40;
    int smallViewportHeight = WINDOW_HEIGHT * 11 / 40;
    int smallViewportX = WINDOW_WIDTH - smallViewportWidth;
    int smallViewportY = 0;

    // Enable scissor test to limit the clearing to the second viewport
    glEnable(GL_SCISSOR_TEST);
    glScissor(smallViewportX, smallViewportY, smallViewportWidth, smallViewportHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    glViewport(smallViewportX, smallViewportY, smallViewportWidth, smallViewportHeight);
    glLoadIdentity();
    std::vector<float> cameraPosition2 = spaceship.getThirdPersonCameraPosition();
    std::vector<float> lookAt2 = spaceship.getThirdPersonLookAt();
    gluLookAt(cameraPosition2[0], cameraPosition2[1], cameraPosition2[2], 
              lookAt2[0], lookAt2[1], lookAt2[2], 
              0.0f, 1.0f, 0.0f);

    // Draw the scene again
    DrawScene();

    // Create a viewport for the top middle corner of the screen
    int topViewportWidth = WINDOW_WIDTH * 3 / 4;
    int topViewportHeight = WINDOW_HEIGHT * 1 / 10;
    int topViewportX = WINDOW_WIDTH * 1 / 8;
    int topViewportY = WINDOW_HEIGHT - topViewportHeight;

    // Enable scissor test to limit the clearing to the third viewport
    glEnable(GL_SCISSOR_TEST);
    glScissor(topViewportX, topViewportY, topViewportWidth, topViewportHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // Set up orthographic projection for the top viewport
    glViewport(topViewportX, topViewportY, topViewportWidth, topViewportHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, topViewportWidth, 0.0, topViewportHeight);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Create and draw the health bar
    //disable depth test
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);
    // draw the score on the top left of the viewport
    glColor3f(1.0f, 1.0f, 1.0f);
    std::string scorestring = "Score: " + std::to_string(score);
    drawText(scorestring.c_str(), 0, 30.0f, GLUT_BITMAP_HELVETICA_18);
    std::string enemiesRemaining = "Enemies Remaining: " + std::to_string(max(CurrentNumberOfEnemies,maxNumberOfEnemiesToSpawned));
    drawText(enemiesRemaining.c_str(), 200, 30.0f, GLUT_BITMAP_HELVETICA_18);
    //number of enemies killed
    std::string enemiesKilled = "Enemies Killed: " + std::to_string(CurrentNumberOfEnemiesKilled);
    drawText(enemiesKilled.c_str(), 200, 50.0f, GLUT_BITMAP_HELVETICA_18);
    // draw the time remaining on the top right of the viewport
    float timeRemaining = (TimeLimit - (currentTime - startTime)) / 1000;
    std::string timeString = "Time Remaining: " + std::to_string(timeRemaining);
    drawText(timeString.c_str(), 0 , 50.0f, GLUT_BITMAP_HELVETICA_18);
    drawHealthBar(0, 0, topViewportWidth, 20.0, 100.0, spaceship.getHealth());
    //enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Swap the front and back buffers to display the scene
    glutSwapBuffers();
}




void GameMaster::DrawGameOver() {
    std::cout << "Drawing game over" << std::endl;
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset the viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Reset the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);

    // Reset the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Reset color
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the title
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    float x = (WINDOW_WIDTH - 200) / 2;
    float y = (WINDOW_HEIGHT - 50) / 2;

    if (result == WIN) {
        drawStrokedText("You Win!", x, y, 0.3f);
        drawStrokedText("Press ESC to return to main menu", x - 100, y - 50, 0.2f);
    } else if (result == LOSE) {
        drawStrokedText("You Lose!", x, y, 0.3f);
        drawStrokedText("Press ESC to return to main menu", x - 100, y - 50, 0.2f);
    } else {
        drawStrokedText("Time Is UP!", x, y + 50, 0.3f);
        drawStrokedText("Game Over!", x, y, 0.3f);
        drawStrokedText("Press ESC to return to main menu", x - 100, y - 50, 0.2f);
    }

    // Swap buffers to display the updated scene
    glutSwapBuffers();
}

void GameMaster::DrawScene() {
    for (GameObject* obj : gameObjects) {
        obj->draw();
    }
}

void GameMaster::addPlanets() {
    // Create the sun from Planet class
    Planet* sun = new Planet();
    sun->setPlanetRadius(1000.0f);
    sun->setCenter(SUN_POSITION);
    sun->setPlanetColor(SUN_COLOR);
    sun->loadTexture("images/sun.jpg");
    gameObjects.push_back(sun);
    planets.push_back(sun);

    // Create mercury planet from Planet class
    Planet* mercury = new Planet();
    mercury->setPlanetRadius(100.0f);
    mercury->setCenter({1150.0f, 1000.0f, 0.0f, 1.0f});
    mercury->setOrbitRadius(1150.0f);
    mercury->setOrbitSpeed(0.0004f);
    mercury->setPlanetColor({0.45f, 0.44f, 0.42f, 1.0f});
    mercury->loadTexture("images/mercury.jpg");
    gameObjects.push_back(mercury);
    planets.push_back(mercury);

    // Create venus planet from Planet class
    Planet* venus = new Planet();
    venus->setPlanetRadius(150.0f);
    venus->setCenter({2500.0f, 1000.0f, 0.0f, 1.0f});
    venus->setOrbitRadius(2600.0f);
    venus->setOrbitSpeed(0.0005f);
    venus->setPlanetColor({1.0f, 0.5f, 0.0f, 1.0f});
    venus->loadTexture("images/venus.jpg");
    gameObjects.push_back(venus);
    planets.push_back(venus);

    // Create earth planet from Planet class
    Planet* earth = new Planet();
    earth->setPlanetRadius(200.0f);
    earth->setCenter({3600.0f, 1000.0f, 0.0f, 1.0f});
    earth->setOrbitRadius(3600.0f);
    earth->setOrbitSpeed(0.00035f);
    earth->setPlanetColor({0.0f, 1.0f, 1.0f, 1.0f});
    earth->loadTexture("images/earth.jpg");
    gameObjects.push_back(earth);
    planets.push_back(earth);

    // Create mars planet from Planet class
    Planet* mars = new Planet();
    mars->setPlanetRadius(180.0f);
    mars->setCenter({4800.0f, 1000.0f, 0.0f, 1.0f});
    mars->setOrbitRadius(4800.0f);
    mars->setOrbitSpeed(0.0003f);
    mars->setPlanetColor({0.9f, 0.15f, 0.05f, 1.0f});
    mars->loadTexture("images/mars.jpg");
    gameObjects.push_back(mars);
    planets.push_back(mars);

    // Create jupiter planet from Planet class
    Planet* jupiter = new Planet();
    jupiter->setPlanetRadius(400.0f);
    jupiter->setCenter({6100.0f, 1000.0f, 0.0f, 1.0f});
    jupiter->setOrbitRadius(6100.0f);
    jupiter->setOrbitSpeed(0.00025f);
    jupiter->setPlanetColor({0.8f, 0.5f, 0.3f, 1.0f});
    jupiter->loadTexture("images/jupiter.jpg");
    gameObjects.push_back(jupiter);
    planets.push_back(jupiter);
    
    // Create saturn planet from Planet class
    Planet* saturn = new Planet();
    saturn->setPlanetRadius(300.0f);
    saturn->setCenter({6900.0f, 1000.0f, 0.0f, 1.0f});
    saturn->setOrbitRadius(6900.0f);
    saturn->setOrbitSpeed(0.0004f);
    saturn->setPlanetColor({0.9f, 0.8f, 0.5f, 1.0f});
    saturn->loadTexture("images/saturn.jpg");
    gameObjects.push_back(saturn);
    planets.push_back(saturn);

    // Create uranus planet from Planet class
    Planet* uranus = new Planet();
    uranus->setPlanetRadius(250.0f);
    uranus->setCenter({7800.0f, 1000.0f, 0.0f, 1.0f});
    uranus->setOrbitRadius(7800.0f);
    uranus->setOrbitSpeed(0.0002f);
    uranus->setPlanetColor({0.5f, 0.8f, 0.9f, 1.0f});
    uranus->loadTexture("images/uranus.jpg");
    gameObjects.push_back(uranus);
    planets.push_back(uranus);

    // Create neptune planet from Planet class
    Planet* neptune = new Planet();
    neptune->setPlanetRadius(200.0f);
    neptune->setCenter({8600.0f, 1000.0f, 0.0f, 1.0f});
    neptune->setOrbitRadius(8600.0f);
    neptune->setOrbitSpeed(0.0003f);
    neptune->setPlanetColor({0.0f, 0.3f, 0.8f, 1.0f});
    neptune->loadTexture("images/neptune.jpg");
    gameObjects.push_back(neptune);
    planets.push_back(neptune);
}

void GameMaster::Update() {
    // Update game logic
    if (state != MAIN_MENU && state != GAME_OVER) {
        int obj_index = 0;
        for (GameObject* obj : gameObjects) {
            for(int other_obj_index = obj_index + 1; other_obj_index < gameObjects.size(); ++other_obj_index){
                gameObjects[other_obj_index] -> checkCollision(obj);
            }
            if (obj->getType() == ObjectType::ENEMYSHIP) {
                EnemyShip* enemy = dynamic_cast<EnemyShip*>(obj);
                float playerPosition[3] = {spaceship.getPositionX(), spaceship.getPositionY(), spaceship.getPositionZ()};
                enemy->update(playerPosition, planets, enemyShips,gameObjects);
            } else {
                obj->update();
            }
            ++obj_index;
        }
    }
    if (state == SURVIVAL_MODE) {
        // Check if it's time to spawn a new enemy
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        if (currentTime - lastTimeEnemySpawned > intervalTimeToSpawnEnemy) {
            if (CurrentNumberOfEnemies < maxNumberOfEnemies) {
                createEnemyShip(currentID, spaceship.getVertices(), enemyColors);
                currentID++;
                CurrentNumberOfEnemies++;
            }
            lastTimeEnemySpawned = currentTime;
        }
    }
    if (state == TIME_MODE) {
        // Check if the time limit has been reached
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        if (currentTime - startTime > TimeLimit) {
            EndGameOver(TIMEISUP);
        }
        if (CurrentNumberOfEnemies == 0 && maxNumberOfEnemiesToSpawned == 0) {
            EndGameOver(WIN);
        }
        // Check if it's time to spawn a new enemy
        if (CurrentNumberOfEnemies < maxNumberOfEnemies && maxNumberOfEnemiesToSpawned > 0) {
            if (currentTime - lastTimeEnemySpawned > intervalTimeToSpawnEnemy) {
                createEnemyShip(currentID, spaceship.getVertices(), enemyColors);
                currentID++;
                CurrentNumberOfEnemies++;
                lastTimeEnemySpawned = currentTime;
                maxNumberOfEnemiesToSpawned--;
            }
        }
    }
    
}

void GameMaster::createEnemyShip(int id, std::vector<float> Vertices, std::vector<float> Colors) {
    // Create an enemy ship with the given ID
    EnemyShip* enemy = new EnemyShip();
    enemy->setId(id);
    // Set the enemy ship's position to a random location
    // within a 20000x2000x20000 cube centered at the origin
    // (the sun is at the origin)
    // The enemy ship will be at least 600 + planets radius units away from all planets use planets vector to check
    //the distance between the enemy ship and the player ship should be at least 1500 units
    // write the code here
    float x = rand() % 20000 - 10000;
    float y = 1000;
    float z = rand() % 20000 - 10000;
    // check if the enemy ship is away from the planets by at least 600 units + planet radius
    for (Planet* planet : planets) {
        float distance = sqrt(pow(x - planet->getPositionX(), 2) + pow(z - planet->getPositionZ(), 2));
        if (distance < 600 + planet->getPlanetRadius()) {
            // The enemy ship is too close to a planet, so move it further away
            x = rand() % 20000 - 10000;
            z = rand() % 20000 - 10000;
            // Restart the loop to check the new position
            planet = planets[0];
        }
    }
    // check if the enemy ship is away from the player ship by at least 1500 units

    float distance = sqrt(pow(x - spaceship.getPositionX(), 2) + pow(z - spaceship.getPositionZ(), 2));
    if (distance < 1500) {
        // The enemy ship is too close to the player ship, so move it further away
        x = rand() % 20000 - 10000;
        z = rand() % 20000 - 10000;
    }

    enemy->setPosition(x, y, z);

    enemy->setScale(1.0f, 1.0f, 1.0f);
    enemy->setMoveSpeed(10.0f);
    enemy->setRotationSpeed(5.0f);
    enemy->setVertices(Vertices);
    enemy->setColors(Colors);
    enemy->setHealth(100);
    enemy->setWeaponPower(10);
    enemyShips.push_back(enemy);
    gameObjects.push_back(enemy);
}

void GameMaster::checkSpaceShipwithinBoundaries() {
    if (spaceship.getPositionX() > 10000) {
        spaceship.setPosition(10000, spaceship.getPositionY(), spaceship.getPositionZ());
    }
    else if (spaceship.getPositionX() < -10000) {
        spaceship.setPosition(-10000, spaceship.getPositionY(), spaceship.getPositionZ());
    }
    if (spaceship.getPositionZ() > 10000) {
        spaceship.setPosition(spaceship.getPositionX(), spaceship.getPositionY(), 10000);
    }
    else if (spaceship.getPositionZ() < -10000) {
        spaceship.setPosition(spaceship.getPositionX(), spaceship.getPositionY(), -10000);
    }
}

void GameMaster::IncreaseScore(int amount) {
    score += amount;
}

void GameMaster::increaseHealth(int amount) {
    int currentHealth = spaceship.getHealth();
    if (currentHealth + amount <= 100) {
        spaceship.setHealth(currentHealth + amount);
    }
}

void GameMaster::decreaseHealth(int amount) {
    int currentHealth = spaceship.getHealth();
    if (currentHealth - amount <= 0) {
        spaceship.setHealth(0);
        EndGameOver(LOSE);
        glutPostRedisplay();
    } else {
        spaceship.setHealth(currentHealth - amount);
    }
}