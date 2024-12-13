/**
 * @file test_002-a.cpp
 * @brief Test implementation of the LibSDL2 library.
 *        I got excited when I saw that the next ch was about canvasses and RGB values,
 *        then heartbroken when it didn't actually involve drawing to anything.  Screw that!
 *        This is largely based on thenumb.at's SDL2 primer
 * @date 121224
 */

#include <SDL.h>
#include <iostream>
using namespace std;

// Commandline arguments MUST be included in main to work with SDL
int main(int argv, char** args) {
    int result;
    SDL_Window* win = NULL;
    SDL_Surface* winSrf = NULL;
    SDL_Surface* image = NULL;

    // Initializes SDL, checking for errors
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        system("pause");
        return 1;
    }

    // Create an actual window
    win = SDL_CreateWindow("Test Window",
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           640, 480,
                           SDL_WINDOW_RESIZABLE);

    // SDL should return NULL pointers if a method fails, or error values if the return isn't a pointer.
    if (!win) {
        cout << "Error creating main window: " << SDL_GetError() << endl;
        system("pause");
        return 1;
    }

    // SDL software rendering uses Surfaces as an abstraction for any raster content
    winSrf = SDL_GetWindowSurface(win);
    if (!winSrf) {
        cout << "Error getting main window surface: " << SDL_GetError() << endl;
        system("pause");
        return 1;
    }

    // Paint the window an odd hue, then update it
    SDL_FillRect(winSrf, NULL, SDL_MapRGB(winSrf->format, 255, 90, 120));
    SDL_UpdateWindowSurface(win);
    
    // Pause execution so we can see our fine work
    system("pause");

    // Now, load a bitmap to a new surface, then "blit" it (copy it) to the main window
    image = SDL_LoadBMP("../res/test/smoko.bmp");
    if (!image) {
        cout << "Error loading image: " << SDL_GetError() << endl;
        system("pause");
        return 1;
    }

    result = SDL_BlitSurface(image, NULL, winSrf, NULL);
    if (result < 0) {
        cout << "Error blitting image to window: " << SDL_GetError() << endl;
        system("pause");
        return 1;
    }

    SDL_UpdateWindowSurface(win);
    
    // Pause execution so we can see our fine work
    system("pause");

    // Clean up memory and shut down
    SDL_DestroyWindow(win);
    win = NULL;
    winSrf = NULL;
    SDL_Quit();
    return 0;
}