#include <iostream>
#include "Renderer.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

SDL_Renderer* gRenderer;
TTF_Font *gFont = NULL;

LTexture::LTexture() {
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::LTexture( SDL_Renderer* renderer, SDL_Texture* texture, int w, int h) {
	mRenderer = renderer;
	mTexture = texture;
	mWidth = w;
	mHeight = h;
}

LTexture::~LTexture() {
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path) {
	// Get rid of preexisting texture
	free();


	// The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if ( loadedSurface == NULL ) {
		std::cout << "Unable to load image" << std::endl;
	} else {
		// Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create Texture
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if ( newTexture == NULL ) {
			std::cout << "Texture couldn't load" << std::endl;
		} else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Free Surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( mRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor ) {
	// Free any preexisting texture
	free();

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if (textSurface == NULL) {
		std::cout << "Unable to render text surface!" << std::endl;
	} else {
		// Create Texture
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface );
		if ( mTexture == NULL ) {
			std::cout << "That didn't seem to work!" << std::endl;
		} else {
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Free old surface
		SDL_FreeSurface( textSurface );
	}

	return mTexture != NULL;
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setAlpha( Uint8 alpha ) {
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

TextureThing::TextureThing() {
	textureID = -1;
	color = {255, 255, 255};
	alpha = 255;
	options = 0;
}

TextureThing::~TextureThing() {
}

TextureThing::TextureThing(int id) {
	textureID = id;
	color = {255, 255, 255};
	alpha = 255;
	options = 0;
}

void TextureThing::setColor(int r, int g, int b) {
	color.r = r;
	color.g = g;
	color.b = b;
	options |= 1;
}

void TextureThing::setAlpha(int al) {
	alpha = al;
	options |= 2;
}

void TextureThing::setClip(SDL_Rect cl) {
	clip = cl;
	options |= 4;
}

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
	int w, h;
	
	if ( loadedSurface == NULL ) {
		std::cout << "Unable to load texture at : " << path << std::endl;
	} else {
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		newTexture = SDL_CreateTextureFromSurface( mRenderer->mRenderer, loadedSurface );
		if ( newTexture == NULL ) {
			std::cout << "Texture couldn't load" << std::endl;
		} else {
			w = loadedSurface->w;
			h = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	LTexture* fruit = new LTexture( mRenderer->mRenderer, newTexture, w, h );

	textureCache.push_back(fruit);
	mTextureCache.push_back(newTexture);

	return textureCache.size()-1;
}
