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
#define MS_PER_FRAME 1000.0/60.0

void processInput(struct app* app);
void update(struct app* app);
void render(struct app* app);
void keydownEvent(void);
void keyupEvent(SDL_Event *e);
long getCurrentTime(void);

struct player player;

double image_x;
double image_y;

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
    while (!app->quit) {
        long start = getCurrentTime();
        processInput(app);
        update(app);
        render(app);
        usleep(start + MS_PER_FRAME - getCurrentTime());
    }
}

long getCurrentTime(void) {
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    return round(spec.tv_nsec / 1.0e6);
}

void processInput(struct app *app) {
    SDL_Event e;
    SDL_PollEvent(&e);
    
    switch (e.type) {
        case SDL_QUIT:
            app->quit = true;
            break;
        case SDL_KEYDOWN:
            printf("keydown\n");
            keydownEvent();
            break;
        case SDL_KEYUP:
            printf("keyup\n");
            break;
        default:
            break;
    }
}

void keydownEvent(void) {
    double x = 0.0;
    double y = 0.0;
    double speed = 5.0;
    
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    
    if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]) {
        y -= speed;
    }
    if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S]) {
        y += speed;
    }
    
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) {
        x += speed;
    }
    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) {
        x -= speed;
    }
    
    updatePlayerSprite(keystate);
    
    player.x += x;
    player.y += y;
}

void keyupEvent(SDL_Event *e) { 
    
}

void update(struct app *app) {
    updatePlayer(&player);
}

void render(struct app *app) {
    renderPlayer(app);
}

void setup(struct app *app) {
    setupPlayer(&player);
}

void destroy(struct app *app) {
    SDL_FreeSurface(app->screenSurface);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}


