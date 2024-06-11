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

void GameMaster::keyUp() {
    spaceship.moveForward();
}

void GameMaster::keyDown() {
    spaceship.moveBackward();
}

void GameMaster::keyLeft() {
    spaceship.moveLeft();
}

void GameMaster::keyRight() {
    spaceship.moveRight();
}

void GameMaster::keySpace() {
    spaceship.fireWeapon();
}

void GameMaster::keyChar(unsigned char key) {
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
}

void GameMaster::GoToMainMenu() {
    updateGameState(MAIN_MENU);
}

void GameMaster::StartSurvivalMode() {
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
    // Draw the survival mode
}

void GameMaster::DrawTimeMode() {
    // Draw the time mode
}

void GameMaster::DrawGameOver() {
    // Draw the game over screen
}

