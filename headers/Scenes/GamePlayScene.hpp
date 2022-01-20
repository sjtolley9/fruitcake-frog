#pragma once

#include "Scene.hpp"

#include "Renderer.hpp"

class GamePlayScene : public Scene {
	private:
		// Textures
		TextureThing splashThing;
		TextureThing pathThing;
		TextureThing ghostyThing;
	public:
		GamePlayScene(Application* app);
		void OnCreate();
		void OnUpdate(uint32_t elapsedTime);
		void OnRender();
};
