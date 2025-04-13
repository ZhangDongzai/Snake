#ifndef SNAKE_INCLUDE_SNAKE_H
#define SNAKE_INCLUDE_SNAKE_H

#include <common.h>
#include <food.h>
#include <menu.h>

#define SNAKE_MOVE_TIME_MS 500

typedef enum {
    DIRECTION_NONE,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} direction;

typedef struct {
    int body[MAP_WIDTH * MAP_HEIGHT][2];
    int length;
    direction direction;
    Uint64 prevTime;
} Snake;

extern Snake snake;

void initSnake();
void updateSnake(Uint64 currentTime);
void renderSnake();

#endif // SNAKE_INCLUDE_SNAKE_H
