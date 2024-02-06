//
//  app.c
//  stardoo
//
//  Created by matty on 2/4/24.
//

#include "app.h"
#include "../player/player.h"
#include <time.h>
#include <unistd.h>

#define WIDTH 1280
#define HEIGHT 720
#define SPEED 0.005
#define HIGH_DELTA 1000.0 / 120.0
#define LOW_DELTA 1000.0 / 30.0

void processInput(struct app* app);
void update(struct app* app, Uint32 deltaTime);
void render(struct app* app);
void keydownEvent(void);
long getCurrentTime(void);

bool keydown = false;

struct player player;
double player_x;
double player_y;

bool init(struct app* app) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL failed to init: %s\n", SDL_GetError());
        return false;
    }
    
    app->window = SDL_CreateWindow("Stardoooo",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   WIDTH,
                                   HEIGHT,
                                   0);
    
    if (app->window == NULL) {
        fprintf(stderr, "SDL window failed to init: %s\n", SDL_GetError());
        return false;
    }
    
    app->screenSurface = SDL_GetWindowSurface(app->window);
    SDL_UpdateWindowSurface(app->window);

    player = (struct player){
        .x = 0,
        .y = 0,
        .name = "matty",
        .health = 100,
        .energy = 100,
    };
    
    return true;
}

void loop(struct app* app) {
    Uint32 last = SDL_GetTicks();
    while (!app->quit) {
        Uint32 current = SDL_GetTicks();
        double deltaTime = current - last;
        processInput(app);
        if (deltaTime > HIGH_DELTA) {
            deltaTime = HIGH_DELTA;
        } else if (deltaTime < LOW_DELTA) {
            deltaTime = LOW_DELTA;
        }
        update(app, deltaTime);
        render(app);
        last = current;
    }
}

void processInput(struct app *app) {
    SDL_Event e;
    SDL_PollEvent(&e);
    
    switch (e.type) {
        case SDL_QUIT:
            app->quit = true;
            break;
        case SDL_KEYDOWN:
            keydownEvent();
            keydown = true;
            break;
        case SDL_KEYUP:
            keydown = false;
            break;
        default:
            break;
    }
}

void keydownEvent(void) {
    double x = 0;
    double y = 0;
    
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    
    if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]) {
        y -= SPEED;
    }
    
    if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S]) {
        y += SPEED;
    }
    
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) {
        x += SPEED;
    }
    
    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) {
        x -= SPEED;
    }
    
    updatePlayerSprite(keystate);
    
    player_x = x;
    player_y = y;
}

void update(struct app *app, Uint32 deltaTime) {
    if (keydown)
        updatePlayer(&player, player_x, player_y, deltaTime);
}

void render(struct app *app) {
    SDL_FillRect(app->screenSurface, NULL, SDL_MapRGB(app->screenSurface->format, 0, 0, 0));
    renderPlayer(app);
    SDL_UpdateWindowSurface(app->window);
}

void setup(struct app *app) {
    setupPlayer(&player);
}

void destroy(struct app *app) {
    SDL_FreeSurface(app->screenSurface);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}


