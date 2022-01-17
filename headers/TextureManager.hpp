#pragma once

#include "Renderer.hpp"

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