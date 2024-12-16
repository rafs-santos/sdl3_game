#include "grid.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <stdint.h>

const Grid::Cor Grid::cores[] = {
    {255, 255, 255, 255}, 
    {0, 0, 0, 255}, 
    {255, 0, 0, 255}, 
    {255, 255, 0, 255}
};




Grid::Grid(/* args */)
{
    // std::cout << "Grid constructor called" << std::endl;
}

Grid::~Grid()
{
    
}

void Grid::init(void){
    for(auto& row : m_grid){
        for(auto& grid_value : row){
            grid_value = 0;
        }
    }
    printGrid();   
}
void Grid::update(void){
    
}
void Grid::newPiece(void){
    
}
void Grid::draw(SDL_Renderer *renderer, float offsetX, float offsetY){
    // std::cout << "width: " << w << " height: "<< h << "\n";
    for(uint8_t y = 0; y < GRID_HEIGHT; y++){
        for(uint8_t x = 0; x < GRID_WIDTH; x++){
            // SDL_FRect block = {(float)(x * BLOCK_SIZE - (w/2) + 1.0F * SHIFT_BLOCK), (float)(y * BLOCK_SIZE - (h/2)+1.0F * SHIFT_BLOCK), (float)BLOCK_SIZE-1.0F * SHIFT_BLOCK, (float)BLOCK_SIZE-1.0F * SHIFT_BLOCK};
            SDL_FRect block = {
                offsetX + (float)(x * BLOCK_SIZE) + 1.0f * SHIFT_BLOCK, 
                offsetY + (float)(y * BLOCK_SIZE) + 1.0f * SHIFT_BLOCK, 
                BLOCK_SIZE - 1.0f * SHIFT_BLOCK, 
                BLOCK_SIZE - 1.0f * SHIFT_BLOCK
            };
            uint8_t color = m_grid[y][x];
            SDL_SetRenderDrawColor(renderer, cores[color].r, cores[color].g, cores[color].b, cores[color].a); // White blocks
            SDL_RenderFillRect(renderer, &block);
        }
    }
}

void Grid::printGrid(void)
{
    for(unsigned int y = 0; y < GRID_HEIGHT; y++){
        for(unsigned int x = 0; x < GRID_WIDTH; x++){
            std::cout << m_grid[y][x] << ' ';
        }
        std::cout << '\n';
    }
}

bool Grid::isCellOutside(int row, int column){
    bool ret = true;
    if(row >= 0 && row < GRID_HEIGHT && column >= 0 && column < GRID_WIDTH){
        ret = false;
    }
    return ret;
}