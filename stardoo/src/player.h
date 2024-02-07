//
//  player.h
//  stardoo
//
//  Created by matty on 2/4/24.
//

#ifndef player_h
#define player_h
#include "app.h"

struct player {
    double x;
    double y;
    const char *name;
    int health;
    int energy;
};

void initPlayer(struct player *player);
void freePlayer(struct player *player);
void renderPlayer(struct app *app);
void setupPlayer(struct player *player);
void updatePlayerSprite(const Uint8* keystate);
void updatePlayer(struct player *player, double x, double y);

#endif /* player_h */
