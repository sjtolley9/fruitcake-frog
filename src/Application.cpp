#include "Application.hpp"

#include <iostream>
#include <cstdint>

Application::Application () {
	// Rendering
	frogRenderer.init();

	// Frame things
	frameTime = 0;
	elapsedTime = 0;
	currentTime = SDL_GetTicks();
	oldTime = SDL_GetTicks();

	// Random Number Stuff
	distribution = std::uniform_real_distribution<double>(1.0,3.0);
	nomalRange = std::uniform_real_distribution<double>(0.0,1.0);
	intRange = std::uniform_int_distribution<int>(0,255);

	// Debug
	#if DEBUG_OUTPUT
	debugCounter = 0;
	debugTick = false;
	#endif
	// Scenes
}

void Application::init () {
	// Scenes
	scenes.push_back(new GamePlayScene(this));
	
	for(Scene* s : scenes)
		s->OnCreate();

	currentScene = 0;
}

void Application::eventHandling () {
	// For event handling
	SDL_Event e;
	// EVENT HANDLING
	while (SDL_PollEvent(&e)) {
		switch(e.type){
			case SDL_QUIT:
				playing = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
		}
	}
}

void Application::render () {
	scenes[currentScene]->OnRender();
}

void Application::update () {
	scenes[currentScene]->OnUpdate(elapsedTime);
}

void Application::run () {
	playing = true;

	while (playing) {
		// FRAME HANDLING
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - oldTime;
		oldTime = currentTime;

		// EVENT HANDLING
		eventHandling();


		// GAME LOGIC
		update();


		// RENDERING
		render();


		#if DEBUG_OUTPUT // DEBUG INFO
		debugCounter += elapsedTime;

		if (DEBUG_OUTPUT && debugCounter > 1000) {
			debugCounter -= 1000;
			debugTick = true;
		}

		if ( debugTick ) {
			std::cout << "Elapsed Time: " << elapsedTime << " | Frame Time: " << frameTime << std::endl;
			debugTick = false;
		}
    
	 	#endif
		
    
    	// DELAY
		frameTime = SDL_GetTicks() - currentTime;

		if (frameTime < 16) {
			SDL_Delay(16-frameTime); // Delay if less than 16 milliseconds
		}

	}

	frogRenderer.close();
}
