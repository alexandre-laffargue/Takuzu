#define __USE_GNU
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include"game.h" 
#include "game_aux.h"


/*****TEST*****/
bool test_dummy()
{
    return true;
}

bool test_game_set_square(){
    game g=game_default();
    game_set_square(g, 0, 0, S_ZERO);
    return true;
}

bool test_game_default_solution(){
    
    game g = game_default_solution();
    if(game_is_over(g)){
        return true;
    }
    else{
        return false;
    }
}

bool test_game_get_square(){
    return true;
}

bool test_game_get_number(){
    return true;
}

bool test_game_get_next_square(){
    return true;
}

bool test_game_get_next_number(){
    return true;
}

bool test_game_is_immutable(){
    return true;
}


/****USAGE****/
void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/****MAIN****/
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage(argc, argv);
    }

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;

    if (strcmp("dummy", argv[1]) == 0){
      ok = test_dummy();
    }

    else if (strcmp("game_set_square", argv[1]) == 0){
      ok = test_game_set_square();
    }

    else if (strcmp("game_default_solution", argv[1]) == 0){
      ok = test_game_default_solution();
    }
    
    else if (strcmp("game_get_square", argv[1]) == 0){
      ok = test_game_get_square();
    }

    else if (strcmp("game_get_number", argv[1]) == 0){
      ok = test_game_get_number();
    }
    else if (strcmp("game_get_next_number", argv[1]) == 0){
      ok = test_game_get_next_number();
    }
    else if (strcmp("game_game_is_immutable", argv[1]) == 0){
      ok = test_game_is_immutable();
    }

    else
    {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // print test result
    if (ok){
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}