#include <food.h>

int food[2];

void freshFood() {
    int map[MAP_WIDTH][MAP_HEIGHT] = {0};
    for (int i = 0; i < snake.length; i++) {
        map[snake.body[i][0]][snake.body[i][1]] = 1;
    }
    
    int total = MAP_WIDTH * MAP_HEIGHT - snake.length;
    int target = SDL_rand(total);

    int count = 0;
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (map[x][y] == 0) {
                if (count == target) {
                    food[0] = x;
                    food[1] = y;
                    return;
                }
                count++;
            }
        }
    }
}

void renderFood() {
    SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_FRect foodRect = {food[0] * MAP_SIZE, food[1] * MAP_SIZE, 
                          MAP_SIZE, MAP_SIZE};
    SDL_RenderFillRect(app.renderer, &foodRect);
}
