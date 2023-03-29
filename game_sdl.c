#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "game_tools.h"
#include "model.h"

int main(int argc, char* argv[]) {
  SDL_Window* window;
  SDL_Renderer* renderer;

  /* Initialize SDL. */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

  /* Create the window where we will draw. */
  window = SDL_CreateWindow("SDL_RenderClear", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 700, 512,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  SDL_SetWindowTitle(window, "takuzu");
  // SDL_SetWindowIcon(window, SDL_Surface* icon);

  /* We must call SDL_CreateRenderer in order for draw calls to affect this
   * window. */
  renderer = SDL_CreateRenderer(window, -1, 0);

  Env* env = init(window, renderer, argc, argv);

  /* main render loop */
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    /* manage events */
    while (SDL_PollEvent(&e)) {
      /* process your events */
      quit = process(window, renderer, env, &e);
      if (quit) break;
    }

    /* background in gray */
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);

    /* render all what you want */
    render(window, renderer, env);
    SDL_RenderPresent(renderer);
    SDL_Delay(DELAY);
  }

  /* clean your environment */
  clean(window, renderer, env);

  /* Always be sure to clean up */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;

  printf("congratulation\n");
  return EXIT_SUCCESS;
}