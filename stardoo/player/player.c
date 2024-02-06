//
//  player.c
//  stardoo
//
//  Created by matty on 2/4/24.
//

#include "player.h"
#include <SDL2/SDL.h>

#define HEIGHT 32
#define WIDTH 32

SDL_Rect image_pos;
SDL_Surface *image = NULL;
int sprite = 5;

SDL_Surface *load_surface(const char *path);

void setupPlayer(struct player *player) {
    image = load_surface("sprite.bmp");
    image_pos.x = player->x;
    image_pos.y = player->y;
    image_pos.w = WIDTH * 8;
    image_pos.h = HEIGHT;
}

void updatePlayerSprite(const Uint8* keystate) {
    if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]) {
        if (sprite == 0) {
            sprite = 1;
        } else {
            sprite = 0;
        }
    }
    
    if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S]) {
        if (sprite == 4) {
            sprite = 5;
        } else {
            sprite = 4;
        }
    }
    
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) {
        if (sprite == 2) {
            sprite = 3;
        } else {
            sprite = 2;
        }
    }
    
    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) {
        if (sprite == 6) {
            sprite = 7;
        } else {
            sprite = 6;
        }
    }
}

void updatePlayer(struct player *player, double x, double y) {
    player->x += x;
    player->y += y;
    image_pos.x = player->x;
    image_pos.y = player->y;
}

void renderPlayer(struct app *app) {
    SDL_Rect clip = {WIDTH * sprite, 0, WIDTH, HEIGHT};
    SDL_BlitSurface(image, &clip, app->screenSurface, &image_pos);
}

SDL_Surface *load_surface(const char *path) {
    SDL_Surface *image = SDL_LoadBMP(path);
    
    if (!image) {
        return 0;
    }
    
    return image;
}
