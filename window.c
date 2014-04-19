#include <SDL2/SDL.h>
#include <stdio.h>

///screen dimensions constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGTH = 480;

int main (int argc, char *args[])
{
    ///The window we'll be rendering to
    SDL_Window *window = NULL;

    ///The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    ///Initialized SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        ///Create window           ///Title
        window = SDL_CreateWindow("Dario Forez", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_SHOWN);
        if (window == 0)
        {
            printf("Window could not be created, SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            ///Get a window surface
            screenSurface = SDL_GetWindowSurface(window);
            ///Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 51, 51, 255));
            ///Update window surface
            SDL_UpdateWindowSurface(window);
            ///Wait two seconds
            SDL_Delay(3000);
        }
    }
    ///Destroy the window
    SDL_DestroyWindow(window);
    ///Quit SDL subsystem
    SDL_Quit();
    return 0;
}
