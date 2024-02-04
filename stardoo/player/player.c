//
//  player.c
//  stardoo
//
//  Created by matty on 2/4/24.
//

#include "player.h"

void move(struct player* player, enum direction direction) {
    switch (direction) {
        case UP:
            player->y += 1;
            break;
        case DOWN:
            player->y -= 1;
            break;
        case LEFT:
            player->x -= 1;
            break;
        case RIGHT:
            player->x += 1;
            break;
    }
}
