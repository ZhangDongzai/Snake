#include <food.h>

int food[2];

void freshFood() {
    SDL_srand(app.framePrevTime);
    food[0] = SDL_rand(10); food[1] = SDL_rand(10);
}

void renderFood() {
    SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_FRect foodRect = {food[0] * MAP_SIZE, food[1] * MAP_SIZE, 
                          MAP_SIZE, MAP_SIZE};
    SDL_RenderFillRect(app.renderer, &foodRect);
}
