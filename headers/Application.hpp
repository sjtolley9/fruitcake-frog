#include <vector>
#include <random>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Renderer.hpp"

#define DEBUG_OUTPUT true
#define GHOSTS 896*20

class Application {
	private:
		// Rendering
		Renderer frogRenderer;
		// Textures
		TextureThing splashThing;
		TextureThing pathThing;
		TextureThing ghostyThing;
		// Random Number Stuff
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution;
		std::uniform_real_distribution<double> nomalRange;
		std::uniform_int_distribution<int> intRange;
		// Debug
		#if DEBUG_OUTPUT
		int debugCounter;
		bool debugTick;
		#endif
		// Frame things
		Uint32 frameTime, elapsedTime, currentTime, oldTime;
		// Game loop things
		bool playing;
	public:
		Application();
		void init();
		void eventHandling();
		void render();
		void run();
};
