#pragma once

#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "TextureManager.hpp"
#include "TextureThing.hpp"
#include "TextureThing.hpp"

class Renderer {
public:
	Renderer();
	~Renderer();
	bool init();
	void close();

	void clearScreen();
	void presentScreen();

	void setFullscreen();
	void setScreenSize(int w, int h);

	void renderThing(TextureThing, int x, int y);
	void newRenderThing(TextureThing, int x, int y);

	TextureManager textureManager;
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;

	friend class TextureManager;
};