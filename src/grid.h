#ifndef GRID_H
#define GRID_H

#include <vector>
#include <array>
#include <SDL3/SDL.h>
#include <stdint.h>

#define GRID_WIDTH      10
#define GRID_HEIGHT     20
#define BLOCK_SIZE      40
#define SHIFT_BLOCK     3

class Grid
{
public:
    Grid(/* args */);
    ~Grid();

    void init(void);
    void printGrid(void);
    void draw(SDL_Renderer *m_renderer, float offsetX, float offsetY);
    bool isCellOutside(int row, int column);
    void update(void);
    void newPiece(void);
private:
    struct Cor {
        uint8_t r, g, b, a;
    };

    static const Cor cores[];
    /* data */
    // std::vector<std::vector<int>> m_grid; // Grid to hold Tetris pieces
    std::array<std::array<int, GRID_WIDTH>, GRID_HEIGHT> m_grid;
    
};




#endif