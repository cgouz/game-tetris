#include <stdio.h>
#include <SDL2/SDL.h>

int main () {

    // Initialize SDL: this code initializes the SDL video subsystem. If it fails, it prints an error message and returns 1.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL init error: %s\n", SDL_GetError());
        return 1;
    }

    // Create an SDL window: this code creates a window with the title "SDL2 Window", centered on the screen, with a width of 640 pixels and a height of 480 pixels. The window is shown immediately. If the window creation fails, it prints an error message, quits SDL, and returns 1.
    SDL_Window *window = SDL_CreateWindow(
        "SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 
        480, 
        SDL_WINDOW_SHOWN
    );

    // Check if the window was created successfully. If not, print an error message, quit SDL, and return 1.
    if (window == NULL) {
        printf("SDL create window error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Wait for 3 seconds: this code pauses the program for 3000 milliseconds (3 seconds) to allow the user to see the window before it is destroyed.
    SDL_Delay(3000); // Wait for 3 seconds

    SDL_DestroyWindow(window); // Destroy the window: this code destroys the window created earlier, freeing up any resources associated with it.
    SDL_Quit(); // Quit SDL: this code cleans up all initialized subsystems and frees any resources used by SDL. It should be called before the program exits to ensure proper cleanup.
    
    return 0;
}