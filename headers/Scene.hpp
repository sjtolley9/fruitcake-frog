#pragma once

#include <cstdint>

class Application;

class Scene {
	protected:
		Application* app;
	public:
		Scene(Application* app);
		virtual void OnCreate() = 0;
		virtual void OnUpdate(uint32_t elapsedTime) = 0;
		virtual void OnRender() = 0;
};

