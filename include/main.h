#ifndef SNAKE_INCLUDE_MAIN_H
#define SNAKE_INCLUDE_MAIN_H

#include <common.h>
#include <food.h>
#include <snake.h>

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    const bool *keyboardState;
    Uint64 framePrevTime;
} App;

extern App app;

#endif // SNAKE_INCLUDE_MAIN_H