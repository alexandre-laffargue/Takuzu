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
#include "game_aux.c"


/* **************************************************************** */

#define BACKGROUND "background_jp.jpg"
#define EMPTY "empty.png"
#define HELP "helpimage.png"
#define ERREUR "erreur.png"
#define KANJIN "kanjiN.png"
#define KANJIB "kanjiB.png"
#define KANJINIM "kanjiNIM.png"
#define KANJIBIM "kanjiBIM.png"
#define HELPTXT "helptxt.png"
#define VICTORY "victory.png"
struct Env_t {
  /* PUT YOUR VARIABLES HERE */
  SDL_Texture *background;
  SDL_Texture *empty;
  SDL_Texture *kanjiN;
  SDL_Texture *kanjiB;
  SDL_Texture *kanjiNIM;
  SDL_Texture *kanjiBIM;
  SDL_Texture *help;
  SDL_Texture *erreur;
  SDL_Texture *helptxt;
  SDL_Texture *victory;
  game g;
  bool showhelp;
};

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[]) {
  Env *env = malloc(sizeof(struct Env_t));
  if (argc == 2){
    char *filename = (char *)argv[1];
    env->g = game_load(filename);
    
  } else {
    env->g = game_default();
  }
  
  
  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if (!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);
  env->empty = IMG_LoadTexture(ren, EMPTY);
  if (!env->empty) ERROR("IMG_LoadTexture: %s\n", EMPTY);
  env->help = IMG_LoadTexture(ren, HELP);
  if (!env->help) ERROR("IMG_LoadTexture: %s\n", HELP);
  env->erreur = IMG_LoadTexture(ren, ERREUR);
  if (!env->erreur) ERROR("IMG_LoadTexture: %s\n", ERREUR);
  env->kanjiN = IMG_LoadTexture(ren, KANJIN);
  if (!env->kanjiN) ERROR("IMG_LoadTexture: %s\n", KANJIN);
  env->kanjiB = IMG_LoadTexture(ren, KANJIB);
  if (!env->kanjiB) ERROR("IMG_LoadTexture: %s\n", KANJIB);
  env->kanjiNIM = IMG_LoadTexture(ren, KANJINIM);
  if (!env->kanjiNIM) ERROR("IMG_LoadTexture: %s\n", KANJINIM);
  env->kanjiBIM = IMG_LoadTexture(ren, KANJIBIM);
  if (!env->kanjiBIM) ERROR("IMG_LoadTexture: %s\n", KANJIBIM);
  env->helptxt = IMG_LoadTexture(ren, HELPTXT);
  if (!env->helptxt) ERROR("IMG_LoadTexture: %s\n", HELPTXT);
  env->victory = IMG_LoadTexture(ren, VICTORY);
  if (!env->victory) ERROR("IMG_LoadTexture: %s\n", VICTORY);
  env->showhelp = false;

  /* PUT YOUR CODE HERE TO INIT TEXTURES, ... */

  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  SDL_RenderCopy(ren, env->background, NULL, NULL);

  int image_width = 50;
  int image_height = 50;
  int rows = game_nb_rows(env->g);
  int cols = game_nb_cols(env->g);
  int x = w / 2;
  int y = h / 2;
  SDL_Rect rect = {w-200, 0, 200, 50};
  SDL_Rect rect3 = {(w/2)-125, 0, 250, 100};
  SDL_RenderCopy(ren, env->helptxt, NULL, &rect);
  if (game_is_over(env->g)) {
    SDL_RenderCopy(ren, env->victory, NULL, &rect3);
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      SDL_Rect rect2 = {(j * image_width) + x - ((cols / 2) * image_width),
                        (i * image_height) + y - ((rows / 2) * image_height),
                        image_width, image_height};
      
        if (game_get_square(env->g, i, j) == S_ONE) {
          SDL_RenderCopy(ren, env->kanjiN, NULL, &rect2);
        } else if (game_get_square(env->g, i, j) == S_ZERO) {
          SDL_RenderCopy(ren, env->kanjiB, NULL, &rect2);
        } else if (game_get_square(env->g, i, j) == S_IMMUTABLE_ONE) {
          SDL_RenderCopy(ren, env->kanjiNIM, NULL, &rect2);
        } else if (game_get_square(env->g, i, j) == S_IMMUTABLE_ZERO) {
          SDL_RenderCopy(ren, env->kanjiBIM, NULL, &rect2);
        } else {
          SDL_RenderCopy(ren, env->empty, NULL, &rect2);
        }

        if(game_has_error(env->g, i, j)){
          SDL_RenderCopy(ren, env->erreur, NULL, &rect2);
        }
      
    }
  }
  if (env->showhelp) {
    SDL_RenderCopy(ren, env->help, NULL, NULL);
  }
  
 
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  int rows = game_nb_rows(env->g);
  int cols = game_nb_cols(env->g);
  int mouse_x;
  int mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  int image_width = 50;
  int image_height = 50;

  if (e->type == SDL_QUIT) {
    return true;
  }

  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
      case SDLK_h:
        env->showhelp = !env->showhelp;
        break;
      case SDLK_r:
        game_restart(env->g);
        break;
      case SDLK_z:
        game_undo(env->g);
        break;
      case SDLK_y:
        game_redo(env->g);
        break;
      case SDLK_SPACE:
        game_play_move(env->g, 0, 0, S_ZERO);
        break;
      case SDLK_k:

        if (mouse_x > w / 2 - ((rows / 2) * image_width) &&
            mouse_x < w / 2 + ((rows / 2) * image_width) &&
            mouse_y > h / 2 - ((cols / 2) * image_height) &&
            mouse_y < h / 2 + ((cols / 2) * image_height)) {
          int x =
              (mouse_x - (w / 2 - ((rows / 2) * image_width))) / image_width;
          int y =
              (mouse_y - (h / 2 - ((cols / 2) * image_height))) / image_height;

          if (game_check_move(env->g, y, x, S_ZERO)) {
            game_play_move(env->g, y, x, S_ZERO);
          }
        }
        break;
      case SDLK_l:

        if (mouse_x > w / 2 - ((rows / 2) * image_width) &&
            mouse_x < w / 2 + ((rows / 2) * image_width) &&
            mouse_y > h / 2 - ((cols / 2) * image_height) &&
            mouse_y < h / 2 + ((cols / 2) * image_height)) {
          int x =
              (mouse_x - (w / 2 - ((rows / 2) * image_width))) / image_width;
          int y =
              (mouse_y - (h / 2 - ((cols / 2) * image_height))) / image_height;

          if (game_check_move(env->g, y, x, S_ONE)) {
            game_play_move(env->g, y, x, S_ONE);
          }
        }
        break;
      case SDLK_e:

        if (mouse_x > w / 2 - ((rows / 2) * image_width) &&
            mouse_x < w / 2 + ((rows / 2) * image_width) &&
            mouse_y > h / 2 - ((cols / 2) * image_height) &&
            mouse_y < h / 2 + ((cols / 2) * image_height)) {
          int x =
              (mouse_x - (w / 2 - ((rows / 2) * image_width))) / image_width;
          int y =
              (mouse_y - (h / 2 - ((cols / 2) * image_height))) / image_height;

          if (game_check_move(env->g, y, x, S_EMPTY)) {
            game_play_move(env->g, y, x, S_EMPTY);
          }
        }
        break;
      case SDLK_s:
        game_solve(env->g);
        break;
      case SDLK_ESCAPE:
        return true;
        break;

      case SDLK_q:
        return true;
        break;
    }
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */

  return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->empty);
  SDL_DestroyTexture(env->kanjiN);
  SDL_DestroyTexture(env->kanjiB);
  SDL_DestroyTexture(env->kanjiNIM);
  SDL_DestroyTexture(env->kanjiBIM);
  SDL_DestroyTexture(env->help);
  SDL_DestroyTexture(env->erreur); 
  game_delete(env->g);
  free(env);
}

/* **************************************************************** */
