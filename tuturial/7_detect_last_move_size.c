#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define ARENA_WIDTH 10
#define ARENA_HEIGHT 20

#define BLOCK_SIZE 20

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

    Uint32 last_fall = SDL_GetTicks();
    // Set the draw color to a shade of grey    
    while (running) {
        SDL_SetRenderDrawColor(
            renderer,
            30,
            30,
            0,
            255
        );

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                running = 0;
                break;
            }
        }


        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_UP] && y > 0) {
            y -= BLOCK_SIZE;
        }

        if (keys[SDL_SCANCODE_DOWN] && y < 480 - BLOCK_SIZE) {
            y += BLOCK_SIZE;
        }

        if (keys[SDL_SCANCODE_LEFT] && x > 0) {
            x -= BLOCK_SIZE;
        }

        if (keys[SDL_SCANCODE_RIGHT] && x < 640 - BLOCK_SIZE) {
            x += BLOCK_SIZE;
        }

        Uint32 now = SDL_GetTicks();

        if (now - last_fall >= 500) {
            if (y < 480 - BLOCK_SIZE) {
                y += BLOCK_SIZE;
            } else {
                y = 0; // Reset to the top if it reaches the bottom
            }

            last_fall = now;
        }
        
        // Butun window'ni yuqorida tanlangan rang bilan to'ldiramiz
        SDL_RenderClear(renderer);

        // Grid rangini tanlaymiz
        SDL_SetRenderDrawColor(
            renderer,
            60,
            60,
            60,
            255
        );

        // Vertical chiziqlar
        for (int x = 0; x <= 640; x += BLOCK_SIZE) {
            SDL_RenderDrawLine(
                renderer,
                x,
                0,
                x,
                480
            );
        }

        // Horizontal chiziqlar
        for (int y = 0; y <= 480; y += BLOCK_SIZE) {
            SDL_RenderDrawLine(
                renderer,
                0,
                y,
                640,
                y
            );
        }

        // draw a white point in the middle of the window
        {
            SDL_SetRenderDrawColor(
                renderer,
                255,
                255,
                255,
                255
            );

            SDL_Rect block = {
                .x = x,
                .y = y,
                .w = 20,
                .h = 20
            };

            // Block'ni chizamiz
            SDL_RenderFillRect(renderer, &block);
        }

        // Chizilgan narsani ekranga chiqaramiz
        SDL_RenderPresent(renderer);
        
        // Delay to limit the frame rate to approximately 60 FPS
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;

}