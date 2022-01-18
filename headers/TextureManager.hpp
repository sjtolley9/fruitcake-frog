#pragma once

#include <vector>

#include "SDL.h"

#include "Renderer.hpp"

class Renderer;

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	bool init(Renderer*);
	void close();

	int createTexture(std::string path);

private:
	Renderer* mRenderer;
	std::vector<SDL_Texture*> mTextureCache;
	friend class Renderer;
};

