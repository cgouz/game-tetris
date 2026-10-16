#include <stdio.h>
#include <SDL2/SDL.h>

int main () {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("ERROR: SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 
        480, 
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("ERROR: SDL_CreateWindow failed: %s\n", SDL_GetError());
    
        SDL_Quit();
    
        return 1;
    }

    SDL_Renderer *renderer  = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("ERROR: SDL_CreateRenderer failed: %s\n", SDL_GetError());
    
        SDL_DestroyWindow(window);
        SDL_Quit();
    
        return 1;
    }

    // set the point coordinates to the center of the window
    int x = 320;
    int y = 240;

    // -- main loop
    int running = 1;

    // Set the draw color to a shade of grey
    while (running) {
        SDL_SetRenderDrawColor(
            renderer,
            30,
            30,
            0,
            255
        );


        // Butun window'ni yuqorida tanlangan rang bilan to'ldiramiz
        SDL_RenderClear(renderer);

        // draw a white point in the middle of the window
        {
            SDL_SetRenderDrawColor(
                renderer,
                255,
                255,
                255,
                255
            );

            SDL_RenderDrawPoint(renderer, x, y);
        }

        // Chizilgan narsani ekranga chiqaramiz
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;

}