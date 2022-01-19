#include "TextureManager.hpp"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Renderer.hpp"

TextureManager::TextureManager() {
	mRenderer = NULL;
}

TextureManager::~TextureManager() {
	mRenderer = NULL;
}

bool TextureManager::init(Renderer* renderer) {
	mRenderer = renderer;

	return mRenderer != NULL;
}

int TextureManager::createTexture( std::string path) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	
	if ( loadedSurface == NULL ) {
		std::cout << "Unable to load texture at : " << path << std::endl;
	} else {
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		newTexture = SDL_CreateTextureFromSurface( mRenderer->mRenderer, loadedSurface );
		if ( newTexture == NULL ) {
			std::cout << "Texture couldn't load" << std::endl;
		} else {
			// Texture Loaded Successfully
		}

		SDL_FreeSurface( loadedSurface );
	}

	//LTexture* fruit = new LTexture( mRenderer->mRenderer, newTexture, w, h );

	//textureCache.push_back(fruit);
	mTextureCache.push_back(newTexture);

	return mTextureCache.size()-1;
}
