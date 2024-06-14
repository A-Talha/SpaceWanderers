#include "GameMaster.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

GameMaster::GameMaster() {
    state = MAIN_MENU; // Initial game state
}

GameMaster::~GameMaster() {
    clearGameObjects();
}

void GameMaster::clearGameObjects() {
    std::cout << "Clearing game objects..." << std::endl;
    for (GameObject* obj : gameObjects) {
        obj = nullptr;
    }
    gameObjects.clear();
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
}

void GameMaster::SpecialKey(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        spaceship.moveForward();
        spaceship.updateFirstPersonView();
        spaceship.updateThirdPersonView();
        break;
    case GLUT_KEY_DOWN:
        spaceship.moveBackward();
        spaceship.updateFirstPersonView();
        spaceship.updateThirdPersonView();
        break;
    case GLUT_KEY_LEFT:
        spaceship.moveLeft();
        spaceship.updateFirstPersonView();
        spaceship.updateThirdPersonView();
        break;
    case GLUT_KEY_RIGHT:
        spaceship.moveRight();
        spaceship.updateFirstPersonView();
        spaceship.updateThirdPersonView();
        break;
    }
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

void GameMaster::keyChar(unsigned char key) {
    switch (key) {
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
        spaceship.updateFirstPersonView();
        spaceship.updateThirdPersonView();
        break;
    case 'x':
        spaceship.RotateRight();
        spaceship.updateFirstPersonView();
        spaceship.updateThirdPersonView();
        break;
    // Add more key controls here for your game
    }
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

    const float SUN_POSITION1[] = {0.0f, 1800.0f, 0.0f, 1.0f}; // x, y, z, w
    const float SUN_COLOR1[] = {1.0f, 1.0f, 0.8f, 1.0f}; // White-yellow light

    // Clear any existing game objects
    clearGameObjects();

    // Create the sun from Planet class
    sun = Planet();
    sun.setPlanetRadius(500.0f);
    sun.setCenter(SUN_POSITION);
    sun.setPlanetColor(SUN_COLOR);
    gameObjects.push_back(&sun);

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
    GLfloat globalAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
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

    std::vector<float> colors;
    for (int i = 0; i < spaceshipVertices.size(); i++) {
        colors.push_back(0);
        colors.push_back(0.9);
        colors.push_back(0.9);
    }

    std::vector<float> enemyColors;
    for (int i = 0; i < spaceshipVertices.size(); i++) {
        enemyColors.push_back(0.9);
        enemyColors.push_back(0);
        enemyColors.push_back(0);
    }

    spaceship.setVertices(spaceshipVertices);
    spaceship.setColors(colors);
    spaceship.updateFirstPersonView();
    spaceship.updateThirdPersonView();

    gameObjects.push_back(&spaceship);

    for (int i = 0; i < 5; i++) {
        EnemyShip* enemy = new EnemyShip();
        enemy->setPosition(1000.0f * (rand() % 10 - 5), 1000.0f, 1000.0f * (rand() % 10 - 5));
        enemy->setScale(1.0f, 1.0f, 1.0f);
        enemy->setMoveSpeed(10.0f);
        enemy->setRotationSpeed(5.0f);
        enemy->setVertices(spaceshipVertices);
        enemy->setColors(enemyColors);
        gameObjects.push_back(enemy);
    }

    updateGameState(SURVIVAL_MODE);
    std::cout << "Survival Mode started." << std::endl;
}


void GameMaster::StartTimeMode() {
    clearGameObjects();
    updateGameState(TIME_MODE);
}

void GameMaster::EndGameOver() {
    clearGameObjects();
    updateGameState(GAME_OVER);
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

    // Swap the front and back buffers to display the scene
    glutSwapBuffers();
}

void GameMaster::DrawTimeMode() {
    // Draw the time mode
}

void GameMaster::DrawGameOver() {
    // Draw the game over screen
}

void GameMaster::DrawScene() {
    for (GameObject* obj : gameObjects) {
        obj->draw();
    }
}

void GameMaster::Update() {
    // Update game logic
    for (GameObject* obj : gameObjects) {
        if (obj->getType() == ObjectType::ENEMYSHIP) {
            EnemyShip* enemy = dynamic_cast<EnemyShip*>(obj);
            float playerPosition[3] = {spaceship.getPositionX(), spaceship.getPositionY(), spaceship.getPositionZ()};
            enemy->update(playerPosition);
        } else {
            obj->update();
        }
    }
}
