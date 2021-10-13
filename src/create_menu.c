#include "header.h"


int create_menu(SDL_Renderer *renderer) {

    bool menu = true;
    SDL_Event event;
    int choose = 0;
    SDL_Texture* background = IMG_LoadTexture(renderer, "resource/images/menu.png");
    SDL_Texture* start = IMG_LoadTexture(renderer, "resource/images/start.png");
    SDL_Texture* settings = IMG_LoadTexture(renderer, "resource/images/settings.png");
    SDL_Texture* quit = IMG_LoadTexture(renderer, "resource/images/quit.png");

    Mix_Chunk *mainClick = Mix_LoadWAV("./resource/sounds/click1.wav");

    SDL_Rect start_for_menu = {X_FOR_START, Y_FOR_START, 350, 150};
    SDL_Rect settings_for_menu = {X_FOR_SETTINGS, Y_FOR_SETTINGS, 350, 150};
    SDL_Rect quit_for_menu = {X_FOR_QUIT, Y_FOR_QUIT, 350, 150};

    bool check = false;

    while (menu)
    {
            SDL_RenderCopy(renderer, background, NULL, NULL);
            SDL_RenderCopy(renderer, start, NULL, &start_for_menu);
            SDL_RenderCopy(renderer, settings, NULL, &settings_for_menu);
            SDL_RenderCopy(renderer, quit, NULL, &quit_for_menu);

        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    
                    if (event.button.button == SDL_BUTTON_LEFT 
                            && event.button.x >= X_FOR_QUIT
                            && event.button.x <= X_FOR_QUIT + 350
                            && event.button.y >= Y_FOR_QUIT
                            && event.button.y <= Y_FOR_QUIT + 150) {
                                Mix_PlayChannel(-1, mainClick, 0);
                                SDL_Delay(100);
                                if (check == false) {
                                    choose = 2;
                                    menu = false; 
                                }
                    }
                    if (event.button.button == SDL_BUTTON_LEFT  
                            && event.button.x >= X_FOR_SETTINGS
                            && event.button.x <= X_FOR_SETTINGS + 350
                            && event.button.y >= Y_FOR_SETTINGS
                            && event.button.y <= Y_FOR_SETTINGS + 150) {
                                Mix_PlayChannel(-1, mainClick, 0);
                                SDL_Delay(100);
                                choose = -1;
                                menu = false;
                    }
                     

                    if (event.button.button == SDL_BUTTON_LEFT  
                            && event.button.x >= X_FOR_START
                            && event.button.x <= X_FOR_START + 350
                            && event.button.y >= Y_FOR_START
                            && event.button.y <= Y_FOR_START + 150) {
                                Mix_PlayChannel(-1, mainClick, 0);
                                SDL_Delay(100);
                                if (check == false) {
                                    choose = 1;
                                    menu = false; 
                                }
                    }
                    break;
                    
                case SDL_QUIT:
                    menu = false;
                    break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    return choose;
}

