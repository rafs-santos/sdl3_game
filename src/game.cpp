
#include "game.h"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <string>
#include <vector>
#include "block.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
// const int BLOCK_SIZE = 20;
// const int SHIFT_BLOCK = 4;
Game::Game() : m_running(true), m_window(nullptr), m_renderer(nullptr), m_grid(), m_currentBlock(1), m_nextBlock(2)
{
}

Game::~Game()
{
}

void Game::draw(void){
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    // Calcula deslocamento para centralizar a grade
    float offsetX = (w - GRID_WIDTH * BLOCK_SIZE) / 2.0f;
    float offsetY = (h - GRID_HEIGHT * BLOCK_SIZE) / 2.0f;

    //draw grid
    m_grid.draw(m_renderer, offsetX, offsetY);
    m_currentBlock.draw(m_renderer, offsetX, offsetY);
}

void Game::init(void){
    // init SDL?
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(std::string("SDL_Init() Error: ") + SDL_GetError());
    }
    // create a window
    m_window = SDL_CreateWindow("HelloWorld SDL3 ttf", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        throw std::runtime_error(std::string("SDL_CreateWindow() Error: ") + SDL_GetError());
    }

    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer) {
        // SDL_Log("SDL_CreateRenderer() Error: ", SDL_GetError());
        throw std::runtime_error(std::string("SDL_CreateRenderer() Error: ") + SDL_GetError());
    }
    m_grid.init();
    // m_currentBlock = Block(1);
    // m_nextBlock = Block(2);

    // print some information about the window
    SDL_ShowWindow(m_window);
    {
        int width, height, bbwidth, bbheight;
        SDL_GetWindowSize(m_window, &width, &height);
        SDL_GetWindowSizeInPixels(m_window, &bbwidth, &bbheight);
        SDL_Log("Window size: %ix%i", width, height);
        SDL_Log("Backbuffer size: %ix%i", bbwidth, bbheight);
        if (width != bbwidth){
            SDL_Log("This is a highdpi environment.");
        }
    }
}

void Game::run(void){
    SDL_Event event;
    unsigned int lastTime = 0, currentTime;
    // Block block(1);
    // main loop
    while (m_running) {
        // Print a report once per second
        lastTime = SDL_GetTicks();
        // go through all pending events until there are no more
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: // triggered on window close
                    m_running = false;
                    break;
                case SDL_EVENT_KEY_DOWN: // triggered when user presses ESC key
                    if (event.key.key == SDLK_ESCAPE) {
                        m_running = false;
                    }
                    else if (event.key.key == SDLK_LEFT) {
                        m_currentBlock.move(0, -1);
                        if (isBlockOutside())
                        {
                            m_currentBlock.move(0, 1);
                        }
                    }
                    else if (event.key.key == SDLK_RIGHT) {
                        m_currentBlock.move(0,1);
                        if (isBlockOutside())
                        {
                            m_currentBlock.move(0, -1);
                        }
                    }
                    else if (event.key.key == SDLK_DOWN) {
                        m_currentBlock.move(1,0);
                        if (isBlockOutside())
                        {
                            m_currentBlock.move(-1, 0);
                        }
                    }
                    else if (event.key.key == SDLK_UP) {
                        m_currentBlock.rotate();
                        if (isBlockOutside())
                        {
                            m_currentBlock.undorotation();
                        }
                    }
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    std::cout << "Teste\n";
                    break;
            }
        }
        // set background color to black
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // for SDL_RenderClear()

        // clear the window to red fade color
        SDL_RenderClear(m_renderer);

        draw();

        // draw everything to screen
        SDL_RenderPresent(m_renderer);
        currentTime = SDL_GetTicks();
        if( (currentTime - lastTime) < SCREEN_TICKS_PER_FRAME){
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - (currentTime - lastTime) );
        }
    }
}

void Game::finish(void){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Game::isBlockOutside(){
    std::vector<Position> tiles = m_currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (m_grid.isCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}