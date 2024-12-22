/**
 * @file test_002-b.cpp
 * @brief Test implementation of the LibSDL2 library.
 *        Focused on event processing and managing a canvas of RGB values.
 *        This is largely based on thenumb.at's SDL2 primer
 * @date 221224
 */

#include <chrono>
#include <SDL.h>
#include <iostream>
#include <memory>
#include <cmath>
#include <thread>
#include "../lib/rt_datatypes.hpp"
using namespace std;


// Structs
// ====================

/**
 * Stores mouse information, such as position in the window and button states.
 * @param x, y: Coordinate of the mouse relative to the window
 * @param x2, y2: The last pixel drawn
 * @param lmb, rmb, mmb: State of the mouse button
 */
struct Mouse {
	int x, y, x2, y2;
	bool lmb = false;
	bool rmb = false;
	bool mmb = false;
	bool init = false;
};

/**
 * A simple class storing our canvas of pixels in a 1d array.
 * @param w, h: The width and height of the canvas
 * @param pixels: The array of pixels in the canvas.  Use index(x, y) to easily get the index of a given pixel in the array.
 * @fn index: A helper function to get the index of a given pixel on the canvas in pixels[]
 */
class Canvas {
	private:
		int w_, h_, arraysize;
	public:
		unique_ptr<rt::RGB[]> pixels;

		// Casting some spells here to allow the pixels_ array to be dynamically sized at creation.
		Canvas(int width, int height);

		// Methods
		void draw_line(rt::RGB color, int x1, int y1, int x2, int y2);

		int index(int x, int y) {
			return (x + (y * w_));
		}

		int w() { return w_; }
		int h() { return h_; }
};


// Function declarations
// ====================

bool sdl_init(int, int);
void sdl_kill();
void process_input_key(SDL_Event*, rt::RGB*);
void process_input_mouse(SDL_Event*, Mouse*, rt::RGB*, Canvas*);
void copy_to_surf(SDL_Surface*, Canvas*, int, int);


// Globals
// ====================

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;


// MAIN
// ====================

// Commandline arguments MUST be included in main to work with SDL
int main(int argv, char** args) {

	// Variables
	int main_width = 640;
	int main_height = 480;
	bool running = true;
	bool resized = false;
	int threads = thread::hardware_concurrency();
	// Canvas
	rt::RGB color = rt::RGB();
	Canvas canvas(main_width, main_height);
	SDL_Rect swatch = {0, 0, 30, 30};
	// Input
	Mouse m1;
	SDL_Event ev;
	// Timers
	chrono::high_resolution_clock clock;
	auto t1 = clock.now();
	auto t2 = t1;

	// Initialize SDL, break if there are errors
	if (!sdl_init(main_width, main_height)) return 1;
	cout << "SDL2 Initialized" << endl;

	// Configure our canvas
	color = rt::RGB(0, 0, 0);
	for (int i=0; i<(main_width*main_height); i++) {
		canvas.pixels[i] = color;
	}
	
	// Main loop
	while (running) {
		// Process all inputs in event queue
		while (SDL_PollEvent(&ev) != 0) {
			// We'll process shutdown commands, mouse events, and keystrokes
			switch (ev.type) {
				case SDL_QUIT:
					running = false;
					break;
			
				case SDL_WINDOWEVENT:
					if (ev.window.event == SDL_WINDOWEVENT_RESIZED
							|| ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						resized = true;
					}
					break;
				
				case SDL_KEYDOWN:
					process_input_key(&ev, &color);
					break;

				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEMOTION:
					process_input_mouse(&ev, &m1, &color, &canvas);
					break;

				default:
					// cout << "Unhandled input: " << ev.type << endl;
					break;
			}
		}

		// Draw on the canvas, if the LMB is down
		if (m1.lmb) {
			canvas.index(m1.x, m1.y);
		}

		t1 = clock.now();
		// Copy the canvas to the window surface, with the power of multithreading
		// Because what MS Paint has been lacking all these years is multithreading
		// This function takes about 5ms to process on a single thread
		if (threads > 1) {
			int row_count = canvas.h() / threads;
			int row_start = 0;
			thread dispatch[threads];
			for (int i=0; i < threads; i++) {
				row_start = i * row_count;
				// Ensure we don't miss the last few lines to a rounding error
				if (i == threads - 1) {
					row_count = canvas.h() - row_start;
				}
				dispatch[i] = thread(copy_to_surf, surface, &canvas, row_start, row_count);
			}
			for (int i=0; i < threads; i++) {
				dispatch[i].join();
			}
		} else {
			copy_to_surf(surface, &canvas, 0, canvas.h());
		}

		// Draw the color swatch to the top left and then update the window
		SDL_FillRect(surface, &swatch, SDL_MapRGB(surface->format, color.r * 255, color.g * 255, color.b * 255));
		SDL_UpdateWindowSurface(window);

		t2 = clock.now();
		cout << (chrono::duration_cast<chrono::microseconds>(t2 - t1).count()) << endl;

		// this_thread::sleep_for(chrono::milliseconds(250));
	}

	sdl_kill();
	return 0;
}

/**
 * Handles initialization of SDL2, returning false if any errors occur.
 * Includes set-up of main window and surface
 */
bool sdl_init(int w, int h) {
	int result;

	// Initializes SDL, checking for errors
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		return false;
	}

	// Create an actual window
	window = SDL_CreateWindow("SDL2 Test",
														SDL_WINDOWPOS_CENTERED,
														SDL_WINDOWPOS_CENTERED,
														w, h,
														0);

	// SDL should return NULL pointers if a method fails, or error values if the return isn't a pointer.
	if (!window) {
		cout << "Error creating main window: " << SDL_GetError() << endl;
		system("pause");
		return false;
	}

	// Create a Surface to use as a buffer for copying from our canvas to the renderer
	// surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	surface = SDL_GetWindowSurface(window);

	if (!surface) {
		cout << "Error getting surface: " << SDL_GetError() << endl;
		system("pause");
		return false;
	}

	return true;
}

/**
 * Cleans up memory and shuts down the SDL pipeline
 */
void sdl_kill() {
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/**
 * Handles keyboard inputs, in this case changing our color swatch
 */
void process_input_key(SDL_Event* ev, rt::RGB* c) {
	bool shift = (ev->key.keysym.mod & KMOD_LSHIFT);
	float delta = 0.1f;
	if (shift) {
		cout << "SHIFT" << endl;
		delta *= -1;
	}

	switch (ev->key.keysym.sym) {
		// SPACE
		case SDLK_SPACE:
			cout << "SPACE" << endl;
			if (ev->type == SDL_KEYDOWN)
			{
				*c = rt::RGB(0, 0, 0);
			}
			break;

		// R
		case SDLK_r:
			cout << "R" << endl;
			c->r += delta;

			if (c->r > 1) {
				c->r = 1;
			} else if (c->r < 0) {
				c->r = 0;
			}
			break;

		// G
		case SDLK_g:
			cout << "G" << endl;
			c->g += delta;

			if (c->g > 1) {
				c->g = 1;
			} else if (c->g < 0) {
				c->g = 0;
			}
			break;

		// B
		case SDLK_b:
			cout << "B" << endl;
			c->b+= delta;

			if (c->b > 1) {
				c->b = 1;
			} else if (c->b < 0) {
				c->b = 0;
			}
			break;

		default:
			break;
	}

	cout << "RGB: " << c->r << " | " << c->g << " | " << c->b << endl;
	return;
}

/**
 * Handles mouse input, drawing to the canvas if LMB is pressed.
 */
void process_input_mouse(SDL_Event* ev, Mouse* mouse, rt::RGB* c, Canvas* canvas) {
	int x = ev->motion.x;
	int y = ev->motion.y;

	if (x > canvas->w()
			|| x < 0
			|| y > canvas->h()
			|| y < 0) {
		mouse->lmb = false;
		return;
	}

	if (!mouse->init) {
		mouse->x = x;
		mouse->y = y;
		mouse->x2 = x;
		mouse->y2 = y;
		mouse->init = true;
	}

	// Update Button states
	if (ev->button.button == SDL_BUTTON_LEFT) {
		if (ev->type == SDL_MOUSEBUTTONDOWN) {
			mouse->lmb = true;
		} else if (ev->type == SDL_MOUSEBUTTONUP) {
			mouse->lmb = false;
		}
	} else if (ev->button.button == SDL_BUTTON_RIGHT) {
		if (ev->type == SDL_MOUSEBUTTONDOWN) {
			mouse->rmb = true;
		} else if (ev->type == SDL_MOUSEBUTTONUP) {
			mouse->rmb = false;
		}
	}

	if (mouse->lmb) {
		if (x != mouse->x || y != mouse->y) {
			canvas->draw_line(*c, mouse->x, mouse->y, x, y);
			mouse->x2 = x;
			mouse->y2 = y;
		}
	}

	if (mouse->rmb) {
		if (x != mouse->x2 || y != mouse->y2) {
			canvas->draw_line(*c, mouse->x2, mouse->y2, x, y);
			mouse->x2 = x;
			mouse->y2 = y;
		}
	}

	// Push the new x, y values to the mouse struct
	mouse->x = x;
	mouse->y = y;
  return;
}

void copy_to_surf(SDL_Surface* surface, Canvas* canvas, int row_start, int row_count) {
	Uint8* srf_pixels;  // Memory location for row y of pixels on our Surface
	int srf_x;  // Memory offset for current pixel x in row y
	rt::RGB pc;  // Pixel color
	int i = canvas->index(0, row_start);
	if ((row_start + row_count) > canvas->h()) {
		row_count = canvas->h() - row_start;
	}

	for (int y = row_start; y < (row_start + row_count); y++) {
		srf_pixels = (Uint8*) surface->pixels + (y * surface->pitch);
		for (int x = 0; x < canvas->w(); x++) {
			pc = canvas->pixels[i];
			srf_x = x * surface->format->BytesPerPixel;
			srf_pixels[srf_x + 0] = (Uint8) (pc.b * 255);
			srf_pixels[srf_x + 1] = (Uint8) (pc.g * 255);
			srf_pixels[srf_x + 2] = (Uint8) (pc.r * 255);
			srf_pixels[srf_x + 3] = 255;
			i++;
		}
	}
}

// Casting some spells here to allow the pixels_ array to be dynamically sized at creation.
Canvas::Canvas(int width, int height)
	: arraysize{width * height}
	, pixels{new rt::RGB[arraysize]}
{
	w_ = width;
	h_ = height;
}

void Canvas::draw_line(rt::RGB color, int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	float x, y, xstep, ystep;  // Current x,y pos along the line, x,y float offset per step
	int steps;

	if (dx == 0 && dy == 0) {
		return;
	}

	if (dx > 0) {
		xstep = 1;
	} else {
		xstep = -1;
	}
	if (dy > 0) {
		ystep = 1;
	} else {
		ystep = -1;
	}
	
	if (dx == 0 || dy == 0) {
		// Simple version: A perfectly horizontal or vertical line
		if (dx == 0) {
			steps = abs(dy);
			xstep = 0;  // Zero out the xstep since the line is horizontal
		} else {
			steps = abs(dx);
			ystep = 0;  // Zero out the ystep since the line is horizontal
		}
	} else {
		// Less simple, it's on some kind of slope
		float slope = (float)dy / (float)dx;
		if (slope > 1 || slope < -1) {
			steps = abs(dy);
			xstep = 1.0f / abs(slope) * xstep;
		} else {
			steps = abs(dx);
			ystep = abs(slope) * ystep;
		}
	}

	x = x1;
	y = y1;

	while (steps > 0) {
		x += xstep;
		y += ystep;
		pixels[index((int)x, (int)y)] = color;
		steps --;
	}

	// cout << "dx: " << dx << " dy: " << dy << endl;
	return;	
}
