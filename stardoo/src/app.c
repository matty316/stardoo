//
//  app.c
//  stardoo
//
//  Created by matty on 2/4/24.
//

#include "app.h"
#include "player.h"
#include <time.h>
#include <unistd.h>

#define WIDTH 1280
#define HEIGHT 720
#define SPEED 1
#define MS_PER_UPDATE 1000.0/120.0

void processInput(struct app* app);
void update(struct app* app);
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
    double lag = 0.0;
    while (!app->quit) {
        Uint32 current = SDL_GetTicks();
        Uint32 deltaTime = current - last;
        last = current;
        lag += deltaTime;
        processInput(app);
        while (lag >= MS_PER_UPDATE) {
            update(app);
            lag -= MS_PER_UPDATE;
        }
        render(app);
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

void update(struct app *app) {
    if (keydown)
        updatePlayer(&player, player_x, player_y);
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


