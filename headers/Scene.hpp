#pragma once

class Application;

class Scene {
	protected:
		Application* app;
	public:
		Scene(Application* app);
		virtual void OnCreate() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
};

