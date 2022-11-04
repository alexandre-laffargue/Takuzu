#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"






void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}



bool test_game_is_empty(){
  game g = game_new_empty();
  for (uint i = 0; i < DEFAULT_SIZE; i++)
  {
    for(uint j = 0; j< DEFAULT_SIZE; j++){
      if (game_get_square(g,i,j)!=S_EMPTY)
      {
       game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);
  return true;
}


bool test_game_play_move(){
  game g = game_new_empty();
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      game_set_square(g,i,j,S_ONE);
    }
  }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      if(  game_get_square(g,i,j)!=S_ONE)
       return false;
    }
    }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      game_set_square(g,i,j,S_EMPTY);
    }
  }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      if(  game_get_square(g,i,j)!=S_EMPTY)
       return false;
    }
    }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      game_set_square(g,i,j,S_ZERO);
    }
  }
  for(uint i = 0; i < DEFAULT_SIZE; i++){
    for(uint j = 0; j < DEFAULT_SIZE; j++){
      if(game_get_square(g,i,j)!=S_ZERO)
       return false;
    }
  }

game_delete(g);
  return true;
}

int main(int argc, char *argv[])
{
  if (argc == 1)
    usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("game_is_empty", argv[1]) == 0)
    ok = test_game_is_empty();
  else if(strcmp("game_play_move", argv[1]) == 0)
    ok = test_game_play_move();

    else{
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);

  }

  if(ok)
  {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  }
  else
  {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}

