#include <vector>
#include <random>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Renderer.hpp"

#include "Scene.hpp"
#include "Scenes/GamePlayScene.hpp"

#define DEBUG_OUTPUT true
#define GHOSTS 896*20

class Application {
	public:
		Application();
		void init();
		void eventHandling();
		void render();
		void update();
		void changeSceneTo(int sceneIndex);
		void pushBackScene(Scene& scene);
		void removeScene(int sceneIndex);
		void popBackScene();
		void run();
	private:
		// Rendering
		Renderer frogRenderer;
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
		// Scenes
		std::vector<Scene*> scenes;
		int currentScene;
		friend class Scene;
		friend class GamePlayScene;
};
