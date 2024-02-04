//
//  app.c
//  stardoo
//
//  Created by matty on 2/4/24.
//

#include "app.h"

#define WIDTH 1280
#define HEIGHT 720

void processInput(struct app* app);
void update(struct app* app);
void render(struct app* app);

SDL_Surface *image = NULL;
SDL_Rect image_pos;
double image_x;
double image_y;

SDL_Surface *load_surface(const char *path);

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
    SDL_FillRect(app->screenSurface, NULL, SDL_MapRGB(app->screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(app->window);
    
    return true;
}

void loop(struct app* app) {
    while (!app->quit) {
        processInput(app);
        update(app);
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
            
            
            break;
        default:
            break;
    }
}

void update(struct app *app) {
    
}

void render(struct app *app) {
    SDL_FillRect(app->screenSurface, NULL, SDL_MapRGB(app->screenSurface->format, 0, 0, 0));
    SDL_BlitSurface(image, NULL, app->screenSurface, &image_pos);
    SDL_UpdateWindowSurface(app->window);
}

void setup(struct app *app) {
    image = load_surface("stick_figure.bmp");
    image_pos.x = 0;
    image_pos.y = 0;
    image_pos.w = 22;
    image_pos.h = 43;
    image_x = 0.0;
    image_y = 0.0;
}

void destroy(struct app *app) {
    SDL_FreeSurface(app->screenSurface);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

SDL_Surface *load_surface(const char *path) {
    SDL_Surface *image = SDL_LoadBMP(path);
    
    if (!image) {
        return 0;
    }
    
    return image;
}
