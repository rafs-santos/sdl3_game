#include "block.h"
#include <SDL3/SDL.h>
#include "grid.h"

#define LBLOCK 1
#define JBLOCK 2
#define IBLOCK 3
#define OBLOCK 4
#define SBLOCK 5
#define TBLOCK 6
#define ZBLOCK 7


Block::Block(unsigned int id) : id(id), m_rotationState(0), m_rowOffset(0), m_columnOffset(0)
{
    switch (id)
    {
    case LBLOCK:
        cells[0] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)};
        cells[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)};
        break;
    case JBLOCK:
        cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)};
        break;
    case IBLOCK:
        cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)};
        cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)};
        cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)};
        break;
    case OBLOCK:
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
        break;
    case SBLOCK:
        cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)};
        cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)};
        cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)};
        break;
    case TBLOCK:
        cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
        break;
    case ZBLOCK:
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)};
        break;
    default:
        break;
    }
}
Block::~Block()
{
}

void Block::draw(SDL_Renderer *renderer, float offsetX, float offsetY){
    std::vector<Position> tiles = getCellPositions();
    for(Position item : tiles){
        SDL_FRect block = {
                offsetX +  (float)((item.column)* BLOCK_SIZE) + 1.0f * SHIFT_BLOCK, 
                offsetY + (float)((item.row)* BLOCK_SIZE) + 1.0f * SHIFT_BLOCK, 
                BLOCK_SIZE - 1.0f * SHIFT_BLOCK, 
                BLOCK_SIZE - 1.0f * SHIFT_BLOCK
        };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // White blocks
        SDL_RenderFillRect(renderer, &block);
    }
}

void Block::move(int row, int column)
{
    m_rowOffset += row;
    m_columnOffset += column;
}

void Block::rotate(void)
{
    m_rotationState++;
    if (m_rotationState == (int)cells.size())
    {
        m_rotationState = 0;
    }
}

void Block::undorotation(void)
{
    m_rotationState--;
    if (m_rotationState == -1)
    {
        m_rotationState = cells.size() - 1;
    }
}

std::vector<Position> Block::getCellPositions()
{
    std::vector<Position> tiles = cells[m_rotationState];
    std::vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + m_rowOffset, item.column + m_columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}