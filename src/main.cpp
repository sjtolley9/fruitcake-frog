/*	This example was sourced from:
	https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
	
	This was used to confirm that SDL2 was configured properly with CMake
*/

#define DEBUG_OUTPUT true

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Renderer.hpp"

#include <random>

#define GHOSTS 896*20

Renderer frogRenderer;

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	frogRenderer.init();

	// Random Number Stuff
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(1.0,3.0);
	std::uniform_real_distribution<double> nomalRange(0.0,1.0);
	std::uniform_int_distribution<int> intRange(0,255);

	TextureThing splashThing(frogRenderer.textureManager.createTexture("assets/splash_logo_small.png"),362,480);
	TextureThing pathThing(frogRenderer.textureManager.createTexture("assets/path.png"),16,16);
	TextureThing ghostyThing(frogRenderer.textureManager.createTexture("assets/ghosty.png"),32,32);
	
	ghostyThing.setAlpha(100);

	int debugCounter = 0;
	bool debugTick = false;

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

		debugCounter += elapsedTime;
		if (DEBUG_OUTPUT && debugCounter > 1000) {
			debugCounter -= 1000;
			debugTick = true;
		}

		// RENDERING
		frogRenderer.clearScreen();

		// Render Splash Logo
		frogRenderer.renderThing(splashThing, 0, 0);

		frogRenderer.presentScreen();

		frameTime = SDL_GetTicks() - currentTime;

		if ( debugTick ) {
			std::cout << "Elapsed Time: " << elapsedTime << " | Frame Time: " << frameTime << std::endl;
			debugTick = false;
		}

		// Delay if less than 16 milliseconds
		if (frameTime < 16) {
			SDL_Delay(16-(SDL_GetTicks()-currentTime));
		}
	}

	frogRenderer.close();

	return 0;
}
