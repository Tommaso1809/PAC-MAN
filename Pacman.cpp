/*Author:Tommaso Polvere 3CI
 *Name:Pacman
 *Description:Implementazione del Pacman Naive in C++,muoviti con i tasti WASD
 */
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <vector>

struct Position {
    int x;
    int y;
};

class PacmanGame {
private:
    static constexpr char WALL = '#';
    static constexpr char EMPTY = ' ';
    static constexpr char PACMAN = '@';
    static constexpr char ENEMY = 'x';
    static constexpr int MAP_HEIGHT = 18;
    static constexpr int MAP_WIDTH = 31;
    
    std::vector<std::vector<char>> gameMap;
    Position pacmanPos{1, 1};
    Position enemyPos;
    
    void generateMaze() {
        // Fill map with walls
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                gameMap[y][x] = WALL;
            }
        }
        
        // Start from position (1,1)
        carvePassage(1, 1);
        
        // Ensure borders are walls
        for (int x = 0; x < MAP_WIDTH; x++) {
            gameMap[0][x] = WALL;
            gameMap[MAP_HEIGHT-1][x] = WALL;
        }
        for (int y = 0; y < MAP_HEIGHT; y++) {
            gameMap[y][0] = WALL;
            gameMap[y][MAP_WIDTH-1] = WALL;
        }
        
        // Add some random openings for better gameplay
        addRandomOpenings();
    }

    void carvePassage(int x, int y) {
        const int directions[4][2] = {{0,2}, {2,0}, {0,-2}, {-2,0}}; // right, down, left, up
        std::vector<int> dirs = {0,1,2,3};
        
        // Randomize directions
        for (int i = dirs.size()-1; i > 0; i--) {
            int j = rand() % (i+1);
            std::swap(dirs[i], dirs[j]);
        }

        gameMap[y][x] = EMPTY;

        // Try each direction
        for (int dir : dirs) {
            int dx = directions[dir][0];
            int dy = directions[dir][1];
            int newX = x + dx;
            int newY = y + dy;
            
            if (newX > 0 && newX < MAP_WIDTH-1 && 
                newY > 0 && newY < MAP_HEIGHT-1 && 
                gameMap[newY][newX] == WALL) {
                // Carve passage
                gameMap[y + dy/2][x + dx/2] = EMPTY;
                carvePassage(newX, newY);
            }
        }
    }

    void addRandomOpenings() {
        const int numOpenings = (MAP_WIDTH * MAP_HEIGHT) / 20; // 5% of map size
        
        for (int i = 0; i < numOpenings; i++) {
            int x = 1 + rand() % (MAP_WIDTH - 2);
            int y = 1 + rand() % (MAP_HEIGHT - 2);
            if (gameMap[y][x] == WALL) {
                // Check if removing this wall won't create a 2x2 empty space
                int emptyNeighbors = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (gameMap[y+dy][x+dx] == EMPTY) emptyNeighbors++;
                    }
                }
                if (emptyNeighbors < 5) {
                    gameMap[y][x] = EMPTY;
                }
            }
        }
    }
    
public:
    PacmanGame() {
        initializeMap();
        generateEnemyPosition();
    }
    
    void initializeMap() {
        gameMap.resize(MAP_HEIGHT, std::vector<char>(MAP_WIDTH));
        generateMaze();
        gameMap[pacmanPos.y][pacmanPos.x] = PACMAN;
    }
    
    void generateEnemyPosition() {
        do {
            enemyPos.x = rand() % (MAP_WIDTH - 2) + 1;
            enemyPos.y = rand() % (MAP_HEIGHT - 2) + 1;
        } while (gameMap[enemyPos.y][enemyPos.x] != EMPTY);
        
        gameMap[enemyPos.y][enemyPos.x] = ENEMY;
    }
    
    void displayMap() const {
        for (const auto& row : gameMap) {
            for (char cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
    }
    
    void start() {
        std::cout << "BENVENUTO IN PACMAN !!\n";
        std::cout << "TU = " << PACMAN << '\n';
        std::cout << "NEMICO = " << ENEMY << '\n';
        std::cout << '\n';
        sleep(2);
        
        displayMap();
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    PacmanGame game;
    game.start();
    
    return 0;
}
