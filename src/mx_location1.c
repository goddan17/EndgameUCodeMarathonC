#include "../inc/header.h"

int mx_location1(SDL_Renderer *renderer) {
    int choose = 0;
    SDL_Event event;
    bool loc_run = true;
    SDL_Texture* location1 = IMG_LoadTexture(renderer, "resource/images/location1.png");
    SDL_Texture* platform_location1 = IMG_LoadTexture(renderer, "resource/images/platform_location1.png");
    SDL_Texture* health_tablo = IMG_LoadTexture(renderer, "resource/images/hearth.png");
    SDL_Texture* hero_stand = IMG_LoadTexture(renderer, "resource/images/stay_rome.png");
    SDL_Texture* hero_run = IMG_LoadTexture(renderer, "resource/images/run_rome.png");
    SDL_Texture* hero_block = IMG_LoadTexture(renderer, "resource/images/block_rome.png");
    SDL_Texture* hero_attack_img = IMG_LoadTexture(renderer, "resource/images/attack_rome.png");
    SDL_Texture* enemy_stand_img = IMG_LoadTexture(renderer, "resource/images/r_stay.png");
    SDL_Texture* enemy_run_img = IMG_LoadTexture(renderer, "resource/images/r_run.png");
    SDL_Texture* enemy_attack_img = IMG_LoadTexture(renderer, "resource/images/r_attack.png");
    SDL_Texture* collumn = IMG_LoadTexture(renderer, "resource/images/collumn_location1.png");
    SDL_Texture* stay_portal = IMG_LoadTexture(renderer, "resource/images/stay_portal.png");

    Mix_Music *mainSound = Mix_LoadMUS("./resource/sounds/location1/music2.mp3"); 
    Mix_PlayMusic(mainSound, -1);

    Mix_Chunk *mainClick = Mix_LoadWAV("./resource/sounds/kick.wav");
    Mix_Chunk *mainJump = Mix_LoadWAV("./resource/sounds/jump.wav");


    t_player hero;
    hero.health = 10;
    hero.pos.x = 40, hero.pos.y = WINDOW_HEIGHT - 280;
    SDL_Rect health_rec[hero.health];
    SDL_Rect health_rec_pix_size_standart = {0, 0, 280, 244};

    t_enemy enemy;
    enemy.health = 1000;
    enemy.pos.x = WINDOW_WIDTH - 500, enemy.pos.y = WINDOW_HEIGHT - 620;

    enum e_orientation orientation = POS_RIGHT;

    bool walk = false, runR = false, runL = false, block = false, hero_attack = false, health_lost = false, enemy_attack = false, enemy_runL = false, enemy_runR = false, enemy_alive = true;
    bool jump = false;
    bool collumn_block_bool_x = false;
    bool collumn_block_bool_y = false;
    int last_hero_y = hero.pos.y;
 
    float fizika = 0.09;

    int counter_jump = 0;
    float speed = JUMP_STEP;
    const char *key;
    time_t time_rn = 0;

    Uint32 ticks, stand, run, block_tick, attack_tick, health_tick, enemy_stand_tick, enemy_run_tick, enemy_attack_tick, portal_stay;

    while (loc_run) {
        ticks = SDL_GetTicks();
        stand = (ticks / 200) % 2;
        run = (ticks / 150) % 3;
        enemy_stand_tick = (ticks / 200) % 2;
        enemy_run_tick = (ticks / 200) % 5;
        block_tick = (ticks / 200) % 2;
        attack_tick = (ticks / 100) % 3;
        enemy_attack_tick = (ticks / 200) % 4;
        health_tick = (ticks / 100) % 5;
        portal_stay = (ticks / 200) % 9;
        SDL_RenderCopy(renderer, location1, NULL, NULL);
        SDL_RenderCopy(renderer, platform_location1, NULL, NULL);
        SDL_Rect collumn_loc = {300, Y_FLOOR, 300, 100};
        SDL_RenderCopy(renderer, collumn, NULL, &collumn_loc);
        SDL_Rect HeroStand = { stand * 60, 0, 60, 60 };
        SDL_Rect HeroRun = { run * 60, 0, 60, 60 };
        SDL_Rect dstrect = { hero.pos.x, hero.pos.y, HERO_WIDTH, HERO_HEIGHT };
        SDL_Rect enemy_dstrect = { enemy.pos.x, enemy.pos.y, 600, 600 };
        SDL_Rect HeroBlock = { 60, 0, 60, 60 };
        SDL_Rect HeroAttack = { attack_tick * 60, 0, 60, 60 };
        SDL_Rect EnemyStand = { enemy_stand_tick * 300, 0, 300, 300 };
        SDL_Rect EnemyRun = { enemy_run_tick * 300, 0, 300, 300 };
        SDL_Rect EnemyAttack = { enemy_attack_tick * 300, 0, 300, 300 };
        SDL_Rect dstrect_for_portal = {X_FOR_PORTAL, Y_FOR_PORTAL, 320, 320 };
        SDL_Rect PortalStay = { portal_stay * 320, 0, 320, 320 };

        for (int i = 0; i < hero.health; i++) {
            health_rec[i].x = HEARTH_TABLO_X + (100 * i) + 10;
            health_rec[i].y = 0;
            health_rec[i].w = 100;
            health_rec[i].h = 100;
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    choose = 2;
                    loc_run = false;
                    break;
                case SDL_KEYUP:
                    walk = false;
                    runL = false;
                    runR = false;
                    block = false;
                    hero_attack = false;
                    break;
                case SDL_KEYDOWN:
                    walk = true;
                    key = SDL_GetKeyName(event.key.keysym.sym);
                    break;
            }
        }

        if (!enemy_alive) {
            SDL_RenderCopy(renderer, stay_portal, &PortalStay, &dstrect_for_portal);
        }

        if (dstrect.x + 40 > collumn_loc.x - 150 && dstrect.x - 10 < collumn_loc.x + 220) {
            collumn_block_bool_x = true;
        }
         else {
            collumn_block_bool_x = false;
        }
        if (dstrect.y + 60 > WINDOW_HEIGHT - 280) {
            collumn_block_bool_y = true;
        }
        else {
            collumn_block_bool_y = false;
        }

        if(!walk) {
            if (orientation == POS_RIGHT && !block && !hero_attack) {
                SDL_RenderCopy(renderer, hero_stand, &HeroStand, &dstrect);
            }
            if (orientation == POS_LEFT && !block && !hero_attack) {
                SDL_RenderCopyEx(renderer, hero_stand, &HeroStand, &dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
            }

        }
        else {
            if(strcmp(key, "Escape") == 0) {
                loc_run = false;   
            }
            else if(strcmp(key, "A") == 0 && block == false && !hero_attack) {
                if (!(hero.pos.x <= LEFT_LIMIT)) {
                    if (!collumn_block_bool_x || !collumn_block_bool_y) {
                        if(jump) {
                            hero.pos.x -= MOVE_STEP * 1.5;
                        } else {
                            hero.pos.x -= MOVE_STEP;
                        }
                    }
                    else {
                        runL = false;
                        hero.pos.x++;
                    }
                }
                runL = true;
                runR = false;
                orientation = POS_LEFT;
            }
            else if(strcmp(key, "D") == 0  && block == false && !hero_attack) {
                if (!(hero.pos.x + HERO_WIDTH >= RIGHT_LIMIT)) {
                    if (!collumn_block_bool_x || !collumn_block_bool_y) {
                        if(jump) {
                            hero.pos.x += MOVE_STEP * 1.5;
                        } else {
                            hero.pos.x += MOVE_STEP;
                        }
                    }
                    else {
                        runR = false;
                        hero.pos.x--;
                    }
                }
                else {
                    if(!enemy_alive) {
                    choose = 4;
                    loc_run = false;
                    }
                }
                runR = true;
                runL = false;
                orientation = POS_RIGHT;
            }
            else if(strcmp(key, "W") == 0 && jump == false) {
                Mix_PlayChannel(-1, mainJump, 0);
                last_hero_y = WINDOW_HEIGHT - 280;
                jump = true;
            }
            else if(strcmp(key, "Q") == 0 && !jump && !hero_attack) {
                block = true;
            }
            else if(strcmp(key, "E") == 0 && !jump && !block) {
                Mix_PlayChannel(-1, mainClick, 0);
                hero_attack = true;
                
            }
            else
                walk = false;
        }

        if (jump == true) {
            block = false;
            hero.pos.y -= speed;
            counter_jump++;
            if (counter_jump == 10) {
                counter_jump = 0;
                speed -= fizika;
                
            }
            if (collumn_block_bool_x) {
                last_hero_y = collumn_loc.y - 230;
            }
            if (hero.pos.y >= last_hero_y && speed < 0) {
                hero.pos.y = last_hero_y;
                jump = false;
                speed = JUMP_STEP;
                counter_jump = 0;
            }
        }

        if (hero.pos.y < WINDOW_HEIGHT - 280 && !collumn_block_bool_x && !jump) {
            hero.pos.y += 2;
            if (hero.pos.y > WINDOW_HEIGHT - 280) {
                hero.pos.y = WINDOW_HEIGHT - 280;
            }
        }
        if (collumn_block_bool_x && collumn_block_bool_y) {
            hero.pos.y = collumn_loc.y - 230;
    
        }

        if (block) {
            walk = false;
        }

        if (hero_attack) {
            walk = false;
        }

        if (hero.pos.x >= 150 && hero.pos.x <= 500) {
            if (hero.pos.y > Y_FLOOR + 150) {
                walk = false;
            }
        }


    
        if (enemy_alive) {
            if (hero_attack) {
                if ((enemy.pos.x + 130 >= hero.pos.x && enemy.pos.x < hero.pos.x) || (enemy.pos.x - 130 <= hero.pos.x && enemy.pos.x > hero.pos.x)) {
                    enemy.health = enemy.health - 1;
                }
            }
            if (!enemy_runL && !enemy_runR && !enemy_attack) {
                 SDL_RenderCopy(renderer, enemy_stand_img, &EnemyStand, &enemy_dstrect);
            }
            if(hero.pos.x < enemy.pos.x - 400 && hero.pos.x < enemy.pos.x + 400) {
                enemy_runL = false;
                enemy_runR = false;
                enemy_attack = false;
            }
            if(hero.pos.x > enemy.pos.x - 400 && hero.pos.x - 100< enemy.pos.x - 130) {
                if (!(enemy.pos.x < collumn_loc.x + 50)) {
                    enemy.pos.x -= MOVE_STEP - 0.25;
                    enemy_runL = false;
                }
                enemy_runL = true;
                enemy_runR = false;
                enemy_attack = false;
            }
            if(hero.pos.x < enemy.pos.x + 400 && hero.pos.x > enemy.pos.x + 130) {
                enemy.pos.x += MOVE_STEP - 0.25;
                enemy_runL = false;
                enemy_runR = true;
                enemy_attack = false;
            }
            if((enemy.pos.x + 130 >= hero.pos.x && enemy.pos.x < hero.pos.x) || (enemy.pos.x - 130 <= hero.pos.x && enemy.pos.x > hero.pos.x)) {
                enemy_runL = false;
                enemy_runR = false;
                enemy_attack = true;
            }
            time_t timer = time(NULL);
        
            if(enemy_attack == true) {
                enemy_runL = false;
                enemy_runR = false;
                if (!block && difftime (timer, time_rn) > 1) {
                    health_lost = true;
                    time_rn = timer;
                }
            }
        }



        if (runL && walk) {
            SDL_RenderCopyEx(renderer, hero_run, &HeroRun, &dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
        }
        else if (runR && walk) {
            SDL_RenderCopy(renderer, hero_run, &HeroRun, &dstrect);
        }
        if (block && orientation == POS_RIGHT) {
            SDL_RenderCopy(renderer, hero_block, &HeroBlock, &dstrect);
        }
        if (block && orientation == POS_LEFT) {
            SDL_RenderCopyEx(renderer, hero_block, &HeroBlock, &dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
        }
        if (hero_attack && orientation == POS_RIGHT) {
            SDL_RenderCopy(renderer, hero_attack_img, &HeroAttack, &dstrect);             
        }
        if (hero_attack && orientation == POS_LEFT) {
            SDL_RenderCopyEx(renderer, hero_attack_img, &HeroAttack, &dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
        }
        if (health_lost && !block) {
            SDL_Rect health_rec_pix_size = {health_tick * 280, 0, 280, 244};
            SDL_RenderCopy(renderer, health_tablo, &health_rec_pix_size, &health_rec[hero.health - 1]);
            if (health_tick == 3) {
                health_lost = false;
                hero.health = hero.health - 1;
            }
        }

        if (enemy_alive) {
            if (enemy_runR) {
                SDL_RenderCopy(renderer, enemy_run_img, &EnemyRun, &enemy_dstrect);
            }
            if (enemy_runL) {
                SDL_RenderCopyEx(renderer, enemy_run_img, &EnemyRun, &enemy_dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
            }
            if (enemy_attack && hero.pos.x < enemy.pos.x + 100) {
                SDL_RenderCopyEx(renderer, enemy_attack_img, &EnemyAttack, &enemy_dstrect, 0, 0, SDL_FLIP_HORIZONTAL);
            }
            if (enemy_attack && hero.pos.x > enemy.pos.x + 100) {
                SDL_RenderCopy(renderer, enemy_attack_img, &EnemyAttack, &enemy_dstrect);
            }
        }


        for (int i = 0; i < hero.health; i++) {
            if (!health_lost) {
                SDL_RenderCopy(renderer, health_tablo, &health_rec_pix_size_standart, &health_rec[i]);
            } 
            else {
                if (i == hero.health - 1) {
                    continue;
                }
                SDL_RenderCopy(renderer, health_tablo, &health_rec_pix_size_standart, &health_rec[i]);
            }
        }

        if (hero.health == 0) {
            choose = 3;
            loc_run = false;
        }

        if (enemy.health == 0) {
          enemy_alive = false;
        }

        SDL_RenderPresent(renderer);
    }
    Mix_FreeMusic(mainSound);
    return choose;
}

