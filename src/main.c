#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define WINDOW_TITLE "Snake"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_FPS 60
#define WINDOW_REFRESH_TIME_MS (1000 / WINDOW_FPS)
#define MAP_SIZE (WINDOW_WIDTH / MAP_WIDTH)
#define SNAKE_MOVE_TIME_MS 500
#define SDL_MAIN_USE_CALLBACKS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


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
} Snake;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static const bool *keyboardState = NULL;
static Uint64 framePrevTime = 0;
static Uint64 snakePrevTime = 0;
static Snake *snake = NULL;
static int food[2];


void initSnake(Snake **snake) {
    *snake = (Snake *)malloc(sizeof(Snake));
    (*snake)->body[0][0] = 1; (*snake)->body[0][1] = 1;
    (*snake)->length = 1;
    (*snake)->direction = DIRECTION_NONE;
    (*snake)->isEat = true;
}


void updateSnake(Snake *snake, Uint64 currentTime) {
    int dx, dy; dx = dy = 0;

    // Set movement direction
    switch (snake->direction) {
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

    if (currentTime - snakePrevTime < SNAKE_MOVE_TIME_MS) return;

    if (snake->body[0][0] + dx == food[0] &&
        snake->body[0][1] + dy == food[1]) {
        snake->isEat = true;
        food[0] = SDL_rand(10); food[1] = SDL_rand(10);
    }
    if (snake->isEat) {
        snake->body[snake->length][0] = snake->body[snake->length - 1][0];
        snake->body[snake->length][1] = snake->body[snake->length - 1][1];
    }

    // Move
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i][0] = snake->body[i-1][0];
        snake->body[i][1] = snake->body[i-1][1];
    }
    snake->body[0][0] += dx;
    snake->body[0][1] += dy;
    if (snake->isEat) {
        snake->length++;
        snake->isEat = false;
    }

    // Out of window
    if (snake->body[0][0] == -1) {
        snake->body[0][0] = MAP_WIDTH - 1;
    } else if (snake->body[0][0] == MAP_WIDTH) {
        snake->body[0][0] = 0;
    } else if (snake->body[0][1] == -1) {
        snake->body[0][1] = MAP_HEIGHT - 1;
    } else if (snake->body[0][1] == MAP_HEIGHT) {
        snake->body[0][1] = 0;
    }

    snakePrevTime = currentTime;
}


void renderSnake(Snake *snake, SDL_Renderer *renderer) {
    SDL_FRect rect; rect.h = rect.w = MAP_SIZE;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < snake->length; i++) {
        rect.x = snake->body[i][0] * MAP_SIZE;
        rect.y = snake->body[i][1] * MAP_SIZE;
        SDL_RenderFillRect(renderer, &rect);
    }
}


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Snake", "1.0", "com.zhangdongzai.snake");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    framePrevTime = snakePrevTime = SDL_GetTicks();
    keyboardState = SDL_GetKeyboardState(NULL);

    // Set food position
    SDL_srand(framePrevTime);
    food[0] = SDL_rand(10); food[1] = SDL_rand(10);

    initSnake(&snake);

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    } else if (keyboardState[SDL_SCANCODE_W] 
        && snake->direction != DIRECTION_DOWN) {
        snake->direction = DIRECTION_UP;
    } else if (keyboardState[SDL_SCANCODE_S] 
        && snake->direction != DIRECTION_UP) {
        snake->direction = DIRECTION_DOWN;
    } else if (keyboardState[SDL_SCANCODE_A] 
        && snake->direction != DIRECTION_RIGHT) {
        snake->direction = DIRECTION_LEFT;
    } else if (keyboardState[SDL_SCANCODE_D] 
        && snake->direction != DIRECTION_LEFT) {
        snake->direction = DIRECTION_RIGHT;
    }
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate) {
    // Control FPS
    Uint64 currentTime = SDL_GetTicks();
    Uint64 delta = currentTime - framePrevTime;

    if (delta < WINDOW_REFRESH_TIME_MS) {
        SDL_Delay(WINDOW_REFRESH_TIME_MS - delta);
    }

    framePrevTime = currentTime;

    updateSnake(snake, currentTime);

    // Render background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render food
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_FRect foodRect = {food[0] * MAP_SIZE, food[1] * MAP_SIZE, 
                          MAP_SIZE, MAP_SIZE};
    SDL_RenderFillRect(renderer, &foodRect);

    renderSnake(snake, renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    free(snake);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
