#ifndef SNAKE_INCLUDE_COMMON_H
#define SNAKE_INCLUDE_COMMON_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WINDOW_TITLE "Snake"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 570
#define WINDOW_FPS 60
#define WINDOW_REFRESH_TIME_MS (1000 / WINDOW_FPS)

#define COLOR_WHITE (SDL_Color) {255, 255, 255, SDL_ALPHA_OPAQUE}
#define COLOR_RED (SDL_Color) {255, 0, 0, SDL_ALPHA_OPAQUE}

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define MAP_SIZE (WINDOW_WIDTH / MAP_WIDTH)

extern int score;
extern bool win;

#endif // SNAKE_INCLUDE_COMMON_H
