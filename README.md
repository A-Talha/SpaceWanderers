# Space Wanderers

Space Wanderers is a simple OpenGL-based space exploration game where you can navigate a spaceship across a vast 10,000 x 10,000 unit map with a sun at the center providing lighting.

## Features

- Navigate a spaceship in a 3D space
- Large map with a sun at the center providing lighting
- Basic transformations (position, rotation, scale) for game objects
- Expandable framework for adding planets, stars, and other game objects

## Controls

- **Arrow Keys**: Move and rotate the spaceship
- **ESC**: Exit the game

## Requirements

- OpenGL
- GLEW
- GLUT/FreeGLUT
- A C++ compiler (e.g., g++)

## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/space-wanderers.git
    cd space-wanderers
    ```

2. **Install dependencies**:
   - Make sure you have OpenGL, GLEW, GLUT/FreeGLUT, SDL, and SDL_mixer installed on your system.

3. **Build the game**:
    ```sh
    g++ SpaceWanderers.cpp GameObject.cpp SpaceShip.cpp GameMaster.cpp Planet.cpp EnemyShip.cpp UI_Functions.cpp FireBullet.cpp -o SpaceWanderers -lopengl32 -lglew32 -lfreeglut -lglu32 -lSDL2 -        lSDL2_mixer -I src/include -L src/lib -m64

    ```

4. **Run the game**:
    ```sh
    ./SpaceWanderers
    ```

## File Structure

- `SpaceWanderers.cpp`: Main game file containing the game loop and OpenGL setup.
- `GameObject.h`: Header file for the `GameObject` class.
- `GameObject.cpp`: Implementation file for the `GameObject` class.
- `README.md`: This file.

## Future Enhancements

- Add planets, stars, and other celestial objects
- Implement collision detection
- Add textures and shaders for better graphics
- Create a scoring system and other game mechanics
