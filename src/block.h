#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <array>
#include <map>
#include <SDL3/SDL.h>
struct Position {
    int row;
    int column;
    Position(int row, int column) : row(row), column(column)
    {}
};


class Block
{
public:
    Block(unsigned int id);
    ~Block();
    unsigned int id;
    std::map<int, std::vector<Position>> cells;

    void draw(SDL_Renderer *renderer, float offsetX, float offsetY);
    void move(int row, int column);
    void rotate(void);
    void undorotation(void);
    std::vector<Position> getCellPositions(void);
private:
    int m_rotationState;
    int m_rowOffset;
    int m_columnOffset;
};





#endif