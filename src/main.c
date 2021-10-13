#include "../inc/header.h"

int main () {
    bool game = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    TTF_Init();
    SDL_Window * window = SDL_CreateWindow("PRODIGAL SON", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    SDL_Cursor* cursor;
    SDL_Surface* cursor_image;
    cursor_image = SDL_LoadBMP("resource/images/cursore.bmp");
    cursor = SDL_CreateColorCursor(cursor_image, 20, 20);
    SDL_SetCursor(cursor);
    Mix_Music *mainSound = Mix_LoadMUS("./resource/sounds/create_menu/musicMENU.mp3");
    Mix_PlayMusic(mainSound, -1);
    
    int choose = 0;
    
    while (game) {
        if (choose == 0) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = create_menu(renderer);
        }
        else if (choose == -1) {
            choose = mx_settings(renderer);
        }
        else if (choose == 1) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = mx_legend(renderer);
        }
        else if (choose == 2) {
            game = false;
        }
        else if (choose == 3) { 
            SDL_ShowCursor(SDL_DISABLE);
            choose = mx_location1(renderer);
        }
        else if (choose == 4) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = mx_legend2(renderer);
        }
        else if (choose == 5) {
            SDL_ShowCursor(SDL_DISABLE);
            choose = mx_location2(renderer);
        }
        else if (choose == 6) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = mx_legend3(renderer);
        }
        else if (choose == 7) {
            SDL_ShowCursor(SDL_DISABLE);
            choose = mx_location3(renderer);
        }
        else if (choose == 8) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = mx_legend4(renderer);
        }
        else if (choose == 88) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = mx_legend4_1(renderer);
        }
        else if (choose == 9) {
            SDL_ShowCursor(SDL_DISABLE);
            choose = mx_location4(renderer);
        }
        else if (choose == 10) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = mx_legend5(renderer);
        }
        else if(choose == 11) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = mx_game_over(renderer);
        }
        else if(choose == 12) {
            SDL_ShowCursor(SDL_ENABLE);
            choose = mx_game_over2(renderer);
        }
    }
    Mix_FreeMusic(mainSound);

    SDL_DestroyRenderer(renderer);
    SDL_FreeCursor(cursor);
    Mix_CloseAudio();
    SDL_FreeSurface(cursor_image);    
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit(); 
    SDL_Quit();
    return 0;     
}

