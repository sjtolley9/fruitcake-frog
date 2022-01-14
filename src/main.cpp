/*	This example was sourced from:
	https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
	
	This was used to confirm that SDL2 was configured properly with CMake
*/

#include <iostream>
#include "SDL.h" 
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "LTexture.hpp"
#include "Renderer.hpp"

SDL_Window *gWindow;

SDL_Rect gSpriteClips[ 40*31 ];

Renderer frogRenderer;

typedef struct frog_struct {
	float x;
	float y;
	float vx;
	float vy;
} frogGuy;

std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

				if ( TTF_Init() == -1) {
					std::cout << "SDL_ttf could not initialize!" << std::endl;
				}
			}
		}
	}

	return success;
}

void close() {
	// Close Fonts
	// Free Textures,
	
	// Destroy Window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main()
{
	init();

	LTexture splashTexture, fontTexture, fontTexture2;
	splashTexture.loadFromFile("assets/splash_logo_small.png");
	gFont = TTF_OpenFont( "assets/lazy.ttf", 28 );
	if ( gFont == NULL ) {
		std::cout << "Couldn't load font! " << TTF_GetError() << std::endl;
	}
	SDL_Color textColor = { 255, 255, 255, 255};

	fontTexture.loadFromRenderedText( "Fruitcake Frog", textColor );
	fontTexture2.loadFromRenderedText( alphabet, textColor );

	Uint32 frameTime = 0, elapsedTime = 0, currentTime = SDL_GetTicks(), oldTime = SDL_GetTicks();

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

		frameTime = elapsedTime;

		// RENDERING

		SDL_RenderClear( gRenderer );

		splashTexture.render(0,0);

		fontTexture.render(640-fontTexture.getWidth(), 480-fontTexture.getHeight());
		fontTexture2.render(640-fontTexture2.getWidth(), 480-fontTexture.getHeight()-fontTexture2.getHeight());

		SDL_RenderPresent( gRenderer );

		frameTime = SDL_GetTicks() - currentTime;

		//std::cout << frameTime << " passed in compute. " << 1000/(1+frameTime) << "fps. Waiting " << (16-frameTime) << std::endl;
		if (frameTime < 16) {
			SDL_Delay(16-(SDL_GetTicks()-currentTime));
		}
	}

	close();

	return 0;
}
