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

    // Set the draw color to a shade of grey
    {
        SDL_SetRenderDrawColor(
            renderer,
            0,
            30,
            0,
            255
        );

        // Butun window'ni yuqorida tanlangan rang bilan to'ldiramiz
        SDL_RenderClear(renderer);

        // Chizilgan narsani ekranga chiqaramiz
        SDL_RenderPresent(renderer);
    }

    SDL_Delay(3000); // Wait for 3 seconds

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;

}