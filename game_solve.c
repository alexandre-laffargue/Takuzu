#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "game_tools.h"

void save_nb_solution(game g, uint nb, char *filename) {
  FILE *f = fopen(filename, "w");
  if (f == NULL) {
    printf("Error: cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  fprintf(f, "%d\n", nb);
  fclose(f);
}

int main(int argc, char const *argv[]) {
  game g;

  if (argc != 3 && argc != 4) {
    printf("Bad argument !!\n");
    return EXIT_FAILURE;
  }

  char *filename = (char *)argv[2];
  g = game_load(filename);
  if (strcmp((char *)argv[1], "-s") == 0) {
    bool ret = game_solve(g);
    if (!ret) {
      return EXIT_FAILURE;
    }
    if (argc == 4) {
      game_save(g, (char *)argv[3]);
    } else {
      game_print(g);
    }
  } else if (strcmp((char *)argv[1], "-c") == 0) {
    uint nb = game_nb_solutions(g);
    if (argc == 4) {
      save_nb_solution(g, nb, (char *)argv[3]);
    } else {
      printf("%d\n", nb);
    }
  } else {
    printf("bad argument !!\n");
  }

  game_delete(g);
  return EXIT_SUCCESS;
}