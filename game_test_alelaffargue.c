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

bool test_game_set_square();

bool test_game_default_solution(){
    
    game g = game_default_solution();
    if(game_is_over(g)){
        return true;
    }
}

bool test_game_get_square();

bool test_game_get_number();

bool test_game_get_next_square();

bool test_game_get_next_number();

bool test_game_is_immutable();


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

    else if (strcmp("game_default_solution", argv[1]) == 0){
      ok = test_game_default_solution();
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