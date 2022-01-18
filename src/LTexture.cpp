#include "LTexture.hpp"

SDL_Renderer* gRenderer;

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