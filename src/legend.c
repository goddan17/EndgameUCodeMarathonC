#include <../inc/header.h>

int mx_legend(SDL_Renderer *renderer) {
    SDL_Event event;
    bool legend = true;
    SDL_Texture* balake = IMG_LoadTexture(renderer, "resource/images/balake.png");
    SDL_Texture* next = IMG_LoadTexture(renderer, "resource/images/next.png");
    SDL_Texture* textlegend1 = IMG_LoadTexture(renderer, "resource/images/textlegend1.png");
    SDL_Texture* hero_stand = IMG_LoadTexture(renderer, "resource/images/stay_father.png");
    SDL_Texture* stay_portal = IMG_LoadTexture(renderer, "resource/images/stay_portal.png");

    SDL_Rect button_next = {X_FOR_NEXT, Y_FOR_NEXT, 138, 65};
    int choose;

    Mix_Music *mainSound = Mix_LoadMUS("./resource/sounds/legends/musicLOADING.mp3"); 
    Mix_PlayMusic(mainSound, -1);

    Mix_Chunk *mainClick = Mix_LoadWAV("./resource/sounds/click1.wav");

    Uint32 ticks, stand, portal_stay;
    
    while (legend) {
        ticks = SDL_GetTicks();
        stand = (ticks / 200) % 2;
        portal_stay = (ticks / 200) % 9;
        SDL_Rect HeroStand = { stand * 60, 0, 60, 60 };
        SDL_Rect PortalStay = { portal_stay * 320, 0, 320, 320 };
        SDL_Rect dstrect = {850, 520, HERO_WIDTH, HERO_HEIGHT };
        SDL_Rect dstrect1 = {1000, 480, 320, 320 };
        
        SDL_RenderCopy(renderer, balake, NULL, NULL);
        SDL_RenderCopy(renderer, next, NULL, &button_next);
        SDL_RenderCopy(renderer, textlegend1, NULL, NULL);
        SDL_RenderCopy(renderer, hero_stand, &HeroStand, &dstrect);
        SDL_RenderCopy(renderer, stay_portal, &PortalStay, &dstrect1);
        
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
                                choose = 3;
                                legend = false;    
                    }
            }
        }
        SDL_RenderPresent(renderer);
    }
    Mix_FreeMusic(mainSound);
    return choose;
}

