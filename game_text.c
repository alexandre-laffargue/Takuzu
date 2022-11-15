#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
void game_help_print() {
  printf("\n> h pour demander de l'aide\n");
  printf("> r pour réinitialiser,\n");
  printf("> q pour quitter,\n");
  printf("> w pour placer un zero/white dans la case <l> <c>\n");
  printf("> b pour placer un one/black dans la case  <l> <c>\n");
  printf("> e pour placer une case vide (empty) à la position <l> <c>\n\n");
}
void game_errors_print(game g) {
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++)
      if (game_has_error(g, i, j)) {
        printf("error in row %d column %d\n", i, j);
      }
  }
}

int main() {
  char c;
  int i, j;
  game g = game_default();
  while (!game_is_over(g)) {
    game_print(g);
    game_errors_print(g);
    scanf("%c", &c);
    switch (c) {
      case 'h':
        game_help_print();
        break;
      case 'r':
        game_restart(g);
        break;
      case 'q':
        game_delete(g);
        printf("shame\n");
        return EXIT_SUCCESS;
        break;
    }
    scanf("%d %d", &i, &j);
    if (c == 'w') {
      if (game_check_move(g, i, j, S_ZERO)) {
        game_play_move(g, i, j, S_ZERO);
      }
    }
  }
}
else if (c == 'b') {
  if (game_check_move(g, i, j, S_ONE)) {
    game_play_move(g, i, j, S_ONE);
  }
}
else if (c == 'e') {
  if (game_check_move(g, i, j, S_EMPTY)) {
    game_play_move(g, i, j, S_EMPTY);
  }
}
}
game_print(g);
printf("congratulation\n");
game_delete(g);
return EXIT_SUCCESS;
}