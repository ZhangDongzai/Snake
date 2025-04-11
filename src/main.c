#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_main.h>
#include <main.h>


App app;
int score = 0;
bool win = false;


void renderScore() {
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(app.renderer, 0, 510, 500, 510);

    char text[9] = "";
    sprintf(text, "SCORE: %02d", score);
    SDL_Surface* textSurface = TTF_RenderText_Blended(app.font, text, 0, COLOR_WHITE);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
    SDL_FRect dstRect = {10, 520, textSurface->w, textSurface->h};
    SDL_RenderTexture(app.renderer, textTexture, NULL, &dstRect);

    if (win) {
        SDL_Surface* textSurfaceWin = TTF_RenderText_Blended(app.font, "WIN", 0, COLOR_RED);
        SDL_Texture* textTextureWin = SDL_CreateTextureFromSurface(app.renderer, textSurfaceWin);
        SDL_FRect dstRectWin = {400, 520, textSurfaceWin->w, textSurfaceWin->h};
        SDL_RenderTexture(app.renderer, textTextureWin, NULL, &dstRectWin);
    }
}


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
    
    freshFood();
    initSnake(&snake);

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

    updateSnake(&snake, currentTime);

    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app.renderer);

    renderFood();
    renderSnake(&snake);
    renderScore();

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
