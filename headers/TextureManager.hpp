#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

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

