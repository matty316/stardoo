//
//  player.h
//  stardoo
//
//  Created by matty on 2/4/24.
//

#ifndef player_h
#define player_h
#include <SDL2/SDL.h>

struct player {
    double x;
    double y;
    const char *name;
    int health;
    int energy;
};

#endif /* player_h */
