#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Renderer;

#include "LTexture.hpp"

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	bool init(Renderer*);
	void close();

	int createTexture(std::string path);

private:
	Renderer* mRenderer;
	std::vector<LTexture*> textureCache;
	std::vector<SDL_Texture*> mTextureCache;
	friend class Renderer;
};