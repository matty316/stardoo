//
//  player.h
//  stardoo
//
//  Created by matty on 2/4/24.
//

#ifndef player_h
#define player_h

enum direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

struct player {
    int x;
    int y;
    const char *name;
    int health;
    int energy;
};

void move(struct player* player, enum direction direction);

#endif /* player_h */
