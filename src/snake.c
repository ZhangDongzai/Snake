#include <snake.h>

Snake snake;

void initSnake() {
    snake.body[0][0] = 1; snake.body[0][1] = 1;
    snake.length = 1;
    snake.direction = DIRECTION_NONE;
    snake.isEat = true;
    snake.prevTime = SDL_GetTicks();
}


void updateSnake(Uint64 currentTime) {
    if (win) return;
    int dx, dy; dx = dy = 0;

    // Set movement direction
    switch (snake.direction) {
    case DIRECTION_UP:
        dy = -1; break;
    case DIRECTION_DOWN:
        dy = 1; break;
    case DIRECTION_LEFT:
        dx = -1; break;
    case DIRECTION_RIGHT:
        dx = 1; break;
    case DIRECTION_NONE:
        return;
    }

    if (currentTime - snake.prevTime < SNAKE_MOVE_TIME_MS) return;

    if (snake.body[0][0] + dx == food[0] &&
        snake.body[0][1] + dy == food[1]) {
        snake.isEat = true;
        freshFood();
        score++;
        if (score >= 99) win = true;
    }
    if (snake.isEat) {
        snake.body[snake.length][0] = snake.body[snake.length - 1][0];
        snake.body[snake.length][1] = snake.body[snake.length - 1][1];
    }

    // Move
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i][0] = snake.body[i-1][0];
        snake.body[i][1] = snake.body[i-1][1];
    }
    snake.body[0][0] += dx;
    snake.body[0][1] += dy;
    if (snake.isEat) {
        snake.length++;
        snake.isEat = false;
    }

    // Out of window
    if (snake.body[0][0] == -1) {
        snake.body[0][0] = MAP_WIDTH - 1;
    } else if (snake.body[0][0] == MAP_WIDTH) {
        snake.body[0][0] = 0;
    } else if (snake.body[0][1] == -1) {
        snake.body[0][1] = MAP_HEIGHT - 1;
    } else if (snake.body[0][1] == MAP_HEIGHT) {
        snake.body[0][1] = 0;
    }
    if (snake.body[0][0] == food[0] &&
        snake.body[0][1] == food[1] && snake.isEat == false) {
        snake.isEat = true;
        freshFood();
        score++;
        if (score >= 99) win = true;
    }

    snake.prevTime = currentTime;
}


void renderSnake() {
    SDL_FRect rect; rect.h = rect.w = MAP_SIZE;

    // Body
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 1; i < snake.length; i++) {
        rect.x = snake.body[i][0] * MAP_SIZE;
        rect.y = snake.body[i][1] * MAP_SIZE;
        SDL_RenderFillRect(app.renderer, &rect);
    }

    // Head
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    rect.x = snake.body[0][0] * MAP_SIZE;
    rect.y = snake.body[0][1] * MAP_SIZE;
    SDL_RenderFillRect(app.renderer, &rect);
}
