#include <menu.h>


int score = 0;


void renderMenu() {
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
