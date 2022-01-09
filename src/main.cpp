/*	This example was sourced from:
	https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
	
	This was used to confirm that SDL2 was configured properly with CMake
*/

#include <iostream>
#include "SDL.h" 
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "LTexture.hpp"

SDL_Window *gWindow;

SDL_Rect gSpriteClips[ 40*31 ];

typedef struct frog_struct {
	float x;
	float y;
	float vx;
	float vy;
} frogGuy;

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL" << std::endl;
		success = false;
	} else {
		// Create SDL window
		gWindow = SDL_CreateWindow(
				"Fruitcake Frog",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				640,
				480,
				0
				);
		if (gWindow == NULL) {
			std::cout << "Window could not be created!" << std::endl;	
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if ( gRenderer == NULL ) {
				std::cout << "Failed to create renderer!" << std::endl;
				success = false;
			} else {
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255);

				int imgFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					std::cout << "SDL_image could not initialize" << std::endl;
					success = false;
				}
			}
		}
	}

	return success;
}

int main(int argc, char *argv[])
{
	init();

	LTexture splashTexture;
	splashTexture.loadFromFile("assets/splash_logo_small.png");

	Uint32 elapsedTime = 0, currentTime = SDL_GetTicks(), oldTime = SDL_GetTicks();

	bool playing = true;
	// For event handling
	SDL_Event e;

	while (playing) {
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - oldTime;
		oldTime = currentTime;

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				playing = false;
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
			}
		}

		// GAME LOGIC

		// RENDERING

		if (elapsedTime == 0) {
			SDL_RenderClear( gRenderer );

			splashTexture.render(0,0);

			SDL_RenderPresent( gRenderer );
		}
	}

	SDL_DestroyWindow(gWindow);
	SDL_Quit();

	return 0;
}
