#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct game_s {
  square* square_array;
  bool wrapping;  // topologie "torique" la colonne la plus à droite est
                  // adjacente à la colonne plus à gauche et la ligne la plus
                  // haute est adjacente à la ligne la plus basse
  bool unique;    // règle du meme nbr de 0 et 1.
  uint nb_rows;
  uint nb_cols;
};