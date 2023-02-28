#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "game_tools.h"



int main(void) {
    game g;
    g = game_new_empty_ext(6, 4, false, false);
    game_set_square(g, 0, 2, S_IMMUTABLE_ONE);
    game_set_square(g, 2, 2, S_IMMUTABLE_ONE);
    //g = game_default();
    //printf(" %d \n",game_solve(g));
    printf(" %d \n",game_nb_solutions(g));
    game_delete(g);
    return EXIT_SUCCESS;
}