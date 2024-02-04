//
//  main.c
//  stardoo
//
//  Created by matty on 2/3/24.
//

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "app/app.h"

int main(int argc, char* argv[]) {    
    struct app app;
    
    if (!init(&app)) {
        return 1;
    }
    setup(&app);
    loop(&app);
    destroy(&app);
    
    return 0;
}
