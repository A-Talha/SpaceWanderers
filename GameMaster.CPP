//GameMaster.CPP
#include "GameMaster.h"


GameMaster::GameMaster() {
    
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

void GameMaster::keyChar(unsigned char key) {
    switch (key) {
    case 27: // ESC key
        exit(0);
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
    updateGameState(MAIN_MENU);
}

void GameMaster::StartSurvivalMode() {
    const float SUN_POSITION1[] = {0.0f, 1000.0f, 0.0f, 1.0f}; // x, y, z, w
    const float SUN_COLOR1[] = {1.0f, 1.0f, 0.8f, 1.0f}; // White-yellow light
    //create the sun from planet class
    sun = Planet();
    sun.setPlanetRadius(500.0f);
    sun.setCenter(SUN_POSITION);
    sun.setPlanetColor(SUN_COLOR);
    gameObjects.push_back(sun);
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
    spaceship.updateFirstPersonView();
    spaceship.updateThirdPersonView();

    updateGameState(SURVIVAL_MODE);
}

void GameMaster::StartTimeMode() {
    updateGameState(TIME_MODE);
}

void GameMaster::EndGameOver() {
    updateGameState(GAME_OVER);
}

void GameMaster::DrawMainMenu() {
    // Draw the main menu
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
    int smallViewportWidth = WINDOW_WIDTH *11/40;
    int smallViewportHeight = WINDOW_HEIGHT *11/40;
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
    sun.draw();
    spaceship.draw();
}

void GameMaster::Update() {
    
}