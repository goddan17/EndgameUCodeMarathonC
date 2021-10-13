#include "header.h"

int mx_settings(SDL_Renderer *renderer) {
    int choose;
    SDL_Event event;
    SDL_Texture* background = IMG_LoadTexture(renderer, "resource/images/menu.png");
    SDL_Texture* button_back = IMG_LoadTexture(renderer, "resource/images/BACK.png");
    SDL_Texture* control = IMG_LoadTexture(renderer, "resource/images/control.png");

    SDL_Rect buttonback = {20, 1000, 138, 65};

    Mix_Chunk *mainClick = Mix_LoadWAV("./resource/sounds/click1.wav");
    
    bool settings = true;
    while (settings) {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, button_back, NULL, &buttonback);
        SDL_RenderCopy(renderer, control, NULL, NULL);
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT:
                    choose = 2;
                    settings = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT
                            && event.button.x >= X_FOR_BACK
                            && event.button.x <= X_FOR_BACK + 138
                            && event.button.y >= Y_FOR_BACK
                            && event.button.y <= Y_FOR_BACK + 65) {
                                Mix_PlayChannel(-1, mainClick, 0);
                                SDL_Delay(100);
                                choose = 0;
                                settings = false;
                                 
                    }
                    
            }    
        }
        SDL_RenderPresent(renderer);
    }
    return choose;
}

