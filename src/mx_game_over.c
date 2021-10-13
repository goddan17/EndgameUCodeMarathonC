#include "header.h"

int mx_game_over(SDL_Renderer *renderer) {
    SDL_Event event;
    bool legend = true;
    SDL_Texture* game_over = IMG_LoadTexture(renderer, "resource/images/game_over_red.png");
    SDL_Texture* button = IMG_LoadTexture(renderer, "resource/images/menu_for_game_over.png");

    Mix_Music *mainSound = Mix_LoadMUS("./resource/sounds/legends/musicLOADING.mp3");
    Mix_PlayMusic(mainSound, -1);
    Mix_Chunk *mainClick = Mix_LoadWAV("./resource/sounds/click1.wav");

    SDL_Rect button1 = {X_FOR_MENU, Y_FOR_MENU, 300, 100};


    int choose;
    Uint32 ticks, game_over_tick;
    while (legend) {
        ticks = SDL_GetTicks();
        game_over_tick = (ticks / 800) % 8;
        SDL_Rect GameOver = { game_over_tick * 1920, 0, 1920, 1080};
        SDL_RenderCopy(renderer, game_over, &GameOver, NULL);
        SDL_RenderCopy(renderer, button, NULL, &button1);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    choose = 2;
                    legend = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT 
                            && event.button.x >= X_FOR_MENU
                            && event.button.x <= X_FOR_MENU + 300
                            && event.button.y >= Y_FOR_MENU
                            && event.button.y <= Y_FOR_MENU + 100) {
                                Mix_PlayChannel(-1, mainClick, 0);
                                SDL_Delay(100);
                                choose = 0;
                                legend = false;
                    }
            }
        }
        SDL_RenderPresent(renderer);
    }
    Mix_FreeMusic(mainSound);
    return choose;
}

