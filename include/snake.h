#ifndef SNAKE_INCLUDE_SNAKE_H
#define SNAKE_INCLUDE_SNAKE_H

#include <common.h>
#include <food.h>

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
    bool isEat;
    Uint64 prevTime;
} Snake;

extern Snake snake;

void initSnake(Snake *snake);
void updateSnake(Snake *snake, Uint64 currentTime);
void renderSnake(Snake *snake);

#endif // SNAKE_INCLUDE_SNAKE_H
