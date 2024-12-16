#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL3/SDL.h>
#include <memory>
#include <vector>
#include "grid.h"
#include "block.h"
class Game
{
public:
    Game(/* args */);
    ~Game();

    // public functions
    void init(void);
    void run(void);
    void finish(void);
    
private:
    /* data */
    bool m_running;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Grid m_grid;
    Block m_currentBlock;
    Block m_nextBlock;

    // private functions
    void draw(void);
    bool isBlockOutside();
};




#endif