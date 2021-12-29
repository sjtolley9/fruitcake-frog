/*	This example was sourced from:
	https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
	
	This was used to confirm that SDL2 was configured properly with CMake
*/

#include <iostream>
#include "SDL.h" 

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(
			"Fruitcake Frog",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640,
			480,
			0
			);

	Uint32 elapsedTime = 0, currentTime = SDL_GetTicks(), oldTime = SDL_GetTicks();

	bool playing = true;
	// For event handling
	SDL_Event e;
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	while (playing) {
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - oldTime;
		oldTime = currentTime;

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				playing = false;
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				std::cout << "(" << x << ", " << y << ")" << std::endl;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
