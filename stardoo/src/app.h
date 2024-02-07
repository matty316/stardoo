//
//  app.h
//  stardoo
//
//  Created by matty on 2/4/24.
//

#ifndef app_h
#define app_h

#include <SDL2/SDL.h>
#include <stdbool.h>

struct app {
    SDL_Window *window;
    SDL_Surface *screenSurface;
    SDL_Renderer *renderer;
    bool quit;
};

bool init(struct app *app);
void setup(struct app *app);
void loop(struct app *app);
void destroy(struct app *app);

#endif /* app_h */
