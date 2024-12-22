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

bool sdl_init();
void sdl_kill();
bool load_image(SDL_Surface*&, string);

// SDL assets that are used by multiple functions
SDL_Window* window = NULL;
SDL_Surface* srf_main = NULL;
SDL_Surface* image;

// Commandline arguments MUST be included in main to work with SDL
int main(int argv, char** args) {
    int result;

    // Initialize SDL, break if there are errors
    if (!sdl_init()) return 1;

    system("pause");

    // Paint the window an odd hue, then update it
    SDL_FillRect(srf_main, NULL, SDL_MapRGB(srf_main->format, 255, 90, 120));
    SDL_UpdateWindowSurface(window);
    
    // Pause execution so we can see our fine work
    system("pause");

    // Load a fun image to display...
    if (!load_image(image, "../res/test/smoko.bmp")) return 1;

    // And display it!
    result = SDL_BlitSurface(image, NULL, srf_main, NULL);
    SDL_UpdateWindowSurface(window);
    
    // Pause execution so we can see our fine work
    system("pause");

    sdl_kill();
    return 0;
}

/**
 * Handles initialization of SDL2, returning false if any errors occur.
 * Includes set-up of main window and surface
 */
bool sdl_init() {
    int result;

    // Initializes SDL, checking for errors
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        system("pause");
        return false;
    }

    // Create an actual window
    window = SDL_CreateWindow("Test Window",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                640, 480,
                                SDL_WINDOW_RESIZABLE);

    // SDL should return NULL pointers if a method fails, or error values if the return isn't a pointer.
    if (!window) {
        cout << "Error creating main window: " << SDL_GetError() << endl;
        system("pause");
        return false;
    }

    // SDL software rendering uses Surfaces as an abstraction for any raster content
    srf_main = SDL_GetWindowSurface(window);
    if (!srf_main) {
        cout << "Error getting main window surface: " << SDL_GetError() << endl;
        system("pause");
        return false;
    }

    return true;
}

void sdl_kill() {
    // Clean up memory and shut down
    SDL_FreeSurface(image);
    
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * Loads a given image to a Surface, formatting it to match the main window surface
 * @param srf: The surface to load the image onto.
 * @param path_to_image: The path (relative or absolute) to the image to be loaded.
 */
bool load_image(SDL_Surface* &srf, string path_to_image) {
    srf = SDL_LoadBMP(path_to_image.c_str());
    if (!srf) {
        cout << "Error loading image: " << SDL_GetError() << endl;
        system("pause");
        return false;
    }
    
    srf = SDL_ConvertSurface(srf, srf_main->format, 0);

    return true;
}