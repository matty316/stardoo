//
//  main.c
//  stardoo
//
//  Created by matty on 2/3/24.
//

#include <SDL2/SDL.h>
#include "app.h"

int main(int argc, char* argv[]) {    
    struct app *app = malloc(sizeof(struct app));
    
    if (!init(app)) {
        return 1;
    }
    setup(app);
    loop(app);
    destroy(app);
    
    return 0;
}
