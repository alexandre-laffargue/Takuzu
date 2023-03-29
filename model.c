// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "model.h"

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_ext.h"
#include "game_tools.h"

/* **************************************************************** */

#define BACKGROUND "background.png"
#define WHITE "white.png"
#define BLACK "black.png"
#define VOID "void.png"
#define EMPTY "empty.png"
struct Env_t {
  /* PUT YOUR VARIABLES HERE */
  SDL_Texture *background;
  SDL_Texture *white;
  SDL_Texture *black;
  SDL_Texture *empty;
  SDL_Texture **cases;
  int **cases_coord;
  game g;
};

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[]) {
  Env *env = malloc(sizeof(struct Env_t));
  env->g = malloc(sizeof(game));

  char *filename = (char *)argv[1];
  env->g = game_load(filename);
  /*int cols = game_nb_cols(env->g);
  int rows = game_nb_rows(env->g);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int n = game_get_number(env->g, i, j);
      if (n == -1) {
        env->cases[(i * cols) + j] = IMG_LoadTexture(ren, EMPTY);
        if (!env->cases[(i * cols) + j]) ERROR("IMG_LoadTexture: %s\n", EMPTY);
      } else if (n == 0) {
        env->cases[(i * cols) + j] = IMG_LoadTexture(ren, BLACK);
        if (!env->cases[(i * cols) + j]) ERROR("IMG_LoadTexture: %s\n", BLACK);
      } else {
        env->cases[(i * cols) + j] = IMG_LoadTexture(ren, WHITE);
        if (!env->cases[(i * cols) + j]) ERROR("IMG_LoadTexture: %s\n", WHITE);
      }
    }
  }*/
  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if (!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);
  env->white = IMG_LoadTexture(ren, WHITE);
  if (!env->white) ERROR("IMG_LoadTexture: %s\n", WHITE);
  env->black = IMG_LoadTexture(ren, BLACK);
  if (!env->black) ERROR("IMG_LoadTexture: %s\n", BLACK);
  env->empty = IMG_LoadTexture(ren, EMPTY);
  if (!env->empty) ERROR("IMG_LoadTexture: %s\n", EMPTY);

  /* PUT YOUR CODE HERE TO INIT TEXTURES, ... */

  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  SDL_Rect rect;
  rect.w = 0;
  rect.h = 0;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  SDL_RenderCopy(ren, env->background, NULL, NULL);

  int image_width = 50;
  int image_height = 50;
  int rows = game_nb_rows(env->g);
  int cols = game_nb_cols(env->g);
  rect.x = w / 2 - rect.w / 2;
  rect.y = h / 2 - rect.h / 2;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      SDL_Rect rect2 = {
          (i * image_width) + rect.x - ((rows / 2) * image_width),
          (j * image_height) + rect.y - ((cols / 2) * image_height),
          image_width, image_height};
      if (game_get_number(env->g, i, j) == 0) {
        SDL_RenderCopy(ren, env->black, NULL, &rect2);
      } else if (game_get_number(env->g, i, j) == 1) {
        SDL_RenderCopy(ren, env->white, NULL, &rect2);
      } else {
        SDL_RenderCopy(ren, env->empty, NULL, &rect2);
      }
    }
  }
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
  if (e->type == SDL_QUIT) {
    return true;
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */

  return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->white);
  SDL_DestroyTexture(env->black);
  SDL_DestroyTexture(env->empty);
  game_delete(env->g);
  free(env);
}

/* **************************************************************** */
