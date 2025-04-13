#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_main.h>
#include <main.h>


App app;
bool win = false;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Snake", "1.0", "com.zhangdongzai.snake");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
        &(app.window), &(app.renderer))) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    app.font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 40);
    if (!app.font) {
        SDL_Log("Couldn't open font: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    app.framePrevTime = SDL_GetTicks();
    app.keyboardState = SDL_GetKeyboardState(NULL);
    SDL_srand(app.framePrevTime);
    
    freshFood();
    initSnake();

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    } else if (app.keyboardState[SDL_SCANCODE_W] 
        && snake.direction != DIRECTION_DOWN) {
        snake.direction = DIRECTION_UP;
    } else if (app.keyboardState[SDL_SCANCODE_S] 
        && snake.direction != DIRECTION_UP) {
        snake.direction = DIRECTION_DOWN;
    } else if (app.keyboardState[SDL_SCANCODE_A] 
        && snake.direction != DIRECTION_RIGHT) {
        snake.direction = DIRECTION_LEFT;
    } else if (app.keyboardState[SDL_SCANCODE_D] 
        && snake.direction != DIRECTION_LEFT) {
        snake.direction = DIRECTION_RIGHT;
    }
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate) {
    // Control FPS
    Uint64 currentTime = SDL_GetTicks();
    Uint64 delta = currentTime - app.framePrevTime;

    if (delta < WINDOW_REFRESH_TIME_MS) {
        SDL_Delay(WINDOW_REFRESH_TIME_MS - delta);
    }

    app.framePrevTime = currentTime;

    updateSnake(currentTime);

    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app.renderer);

    renderSnake();
    renderFood();
    renderMenu();

    SDL_RenderPresent(app.renderer);

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    TTF_CloseFont(app.font);
    TTF_Quit();
    SDL_Quit();
}
