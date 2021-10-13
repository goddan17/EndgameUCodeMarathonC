#include <../inc/header.h>

int mx_legend3(SDL_Renderer *renderer) {
    SDL_Event event;
    bool legend = true;
    SDL_Texture* balake = IMG_LoadTexture(renderer, "resource/images/balake.png");
    SDL_Texture* next = IMG_LoadTexture(renderer, "resource/images/next.png");
    SDL_Texture* textlegend1 = IMG_LoadTexture(renderer, "resource/images/textlegend3.png");
    SDL_Texture* hero_stand = IMG_LoadTexture(renderer, "resource/images/stay_knight.png");
    

    Mix_Music *mainSound = Mix_LoadMUS("./resource/sounds/legends/musicLOADING.mp3"); 
    Mix_PlayMusic(mainSound, -1);

    Mix_Chunk *mainClick = Mix_LoadWAV("./resource/sounds/click1.wav");

    SDL_Rect button_next = {X_FOR_NEXT, Y_FOR_NEXT, 138, 65};
    int choose;
    Uint32 ticks, stand;
    while (legend) {
        ticks = SDL_GetTicks();
        stand = (ticks / 200) % 2;
        SDL_Rect HeroStand = { stand * 60, 0, 60, 60 };
        SDL_Rect dstrect = {850, 590, HERO_WIDTH, HERO_HEIGHT };
        
        SDL_RenderCopy(renderer, balake, NULL, NULL);
        SDL_RenderCopy(renderer, next, NULL, &button_next);
        SDL_RenderCopy(renderer, textlegend1, NULL, NULL);
        SDL_RenderCopy(renderer, hero_stand, &HeroStand, &dstrect);
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    choose = 2;
                    legend = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT 
                            && event.button.x >= X_FOR_NEXT
                            && event.button.x <= X_FOR_NEXT + 138
                            && event.button.y >= Y_FOR_NEXT
                            && event.button.y <= Y_FOR_NEXT + 65) {
                                Mix_PlayChannel(-1, mainClick, 0);
                                SDL_Delay(100);
                                choose = 7;
                                legend = false;
                    }
            }
        }
        SDL_RenderPresent(renderer);
    }
    Mix_FreeMusic(mainSound);
    return choose;
}

