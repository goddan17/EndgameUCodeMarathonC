#ifndef HEADER_H
#define HEADER_H

#define X_FOR_START 100
#define Y_FOR_START 70
#define X_FOR_SETTINGS 100
#define Y_FOR_SETTINGS 250
#define X_FOR_QUIT 100
#define Y_FOR_QUIT 430
#define X_FOR_NEXT 1750
#define Y_FOR_NEXT 30
#define X_FOR_BACK 20
#define Y_FOR_BACK 1000
#define X_FOR_PORTAL 1700
#define Y_FOR_PORTAL 730


#define X_FOR_MENU 810
#define Y_FOR_MENU 900

#define HEARTH_TABLO_X 20
#define HEARTH_TABLO_Y 20

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define HERO_WIDTH      250
#define HERO_HEIGHT     250
#define PIXEL_WIDTH     128
#define PIXEL_HEIGHT    128
#define PIXEL_SIZE      100
#define MOVE_STEP       0.5
#define JUMP_STEP       2
#define JUMP_HEIGHT     250
#define LEFT_LIMIT      -55
#define RIGHT_LIMIT     1975
#define health_count    5

#define Y_FLOOR 940




#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h" 
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <locale.h>
#include <time.h>

enum e_orientation {
    POS_RIGHT,
    POS_LEFT
};

typedef struct s_position {
    float x;
    float y;
}              t_position;

typedef struct s_player {
    t_position pos;
    int health;
}               t_player;

typedef struct s_enemy {
    t_position pos;
    int health;
}               t_enemy;

/*typedef struct s_health {
    int hearth[health_count];
}               t_health;*/ 

int mx_location1(SDL_Renderer *renderer);
int create_menu(SDL_Renderer *renderer);

int mx_legend(SDL_Renderer *renderer);

int mx_location3(SDL_Renderer *renderer);
int mx_location2(SDL_Renderer *renderer);
int mx_location1(SDL_Renderer *renderer);
int mx_legend2(SDL_Renderer *renderer);
int mx_settings(SDL_Renderer *renderer);
int mx_legend3(SDL_Renderer *renderer);
int mx_location4(SDL_Renderer *renderer);
int mx_legend4(SDL_Renderer *renderer);
int mx_legend5(SDL_Renderer *renderer);
int mx_legend4_1(SDL_Renderer *renderer);
int mx_game_over(SDL_Renderer *renderer);
int mx_game_over2(SDL_Renderer *renderer);


#endif

