#include "Scenes/GamePlayScene.hpp"

#include <iostream>

#include "Application.hpp"

GamePlayScene::GamePlayScene(Application* app)
	: Scene(app)
{}

void GamePlayScene::OnCreate(){
	// Textures
	splashThing = TextureThing(app->frogRenderer.textureManager.createTexture("assets/splash_logo_small.png"),362,480);
	pathThing = TextureThing(app->frogRenderer.textureManager.createTexture("assets/path.png"),16,16);
	ghostyThing = TextureThing(app->frogRenderer.textureManager.createTexture("assets/ghosty.png"),32,32);

	ghostyThing.setAlpha(100);
}

void GamePlayScene::OnUpdate(Uint32 elapsedTime){
}

void GamePlayScene::OnRender(){
	app->frogRenderer.clearScreen();
	app->frogRenderer.renderThing(splashThing, 0, 0);// Render Splash Logo
	app->frogRenderer.presentScreen();
}
