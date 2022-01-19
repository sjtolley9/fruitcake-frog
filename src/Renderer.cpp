#include "Renderer.hpp"

#include <iostream>

Renderer::Renderer() {
	
}

Renderer::~Renderer() {

}

bool Renderer::init() {
	bool success = true;

	// Initialize SLD, if this fails we're doomed!
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	} else {
		// Set texture filtering to linear
		if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}

		// Set texture filtering to linear
		mWindow = SDL_CreateWindow(
				"Fruitcake Frog",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				640,
				480,
				0
				);
		if ( mWindow == NULL ) {
			std::cout << "Window could not be created!" << std::endl;
			success = false;
		} else {
			mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED );
			if ( mRenderer == NULL ) {
				std::cout << "Failed to create Renderer!" << std::endl;
				success = false;
			} else {
				SDL_SetRenderDrawColor( mRenderer, 0, 0, 0, 255);

				int imgFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					std::cout << "SDL_image could not initialize" << std::endl;
					success = false;
				}

				if ( TTF_Init() == -1) {
					std::cout << "SDL_ttf could not initialize!" << std::endl;
				}
			}
		}
	}

	textureManager.init(this);

	return success;
}

void Renderer::close() {
	SDL_DestroyRenderer( mRenderer );
	SDL_DestroyWindow( mWindow );
	mWindow = NULL;
	mRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Renderer::clearScreen() {
	SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( mRenderer );
}

void Renderer::presentScreen() {
	SDL_RenderPresent( mRenderer );
}

void Renderer::setFullscreen() {
	SDL_DisplayMode dm;
	
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
		std::cout << "Fullscreen error" << std::endl;
	}
	
	SDL_SetWindowSize(mWindow, dm.w, dm.h);
	SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
}

void Renderer::setScreenSize(int w, int h) {
	SDL_SetWindowSize(mWindow, w, h);
	SDL_SetWindowFullscreen(mWindow, 0);
}

void Renderer::renderThing(TextureThing tt, int x, int y) {
	SDL_Texture* texture = textureManager.mTextureCache[tt.textureID];
	SDL_Rect* clipper = NULL;

	SDL_Rect renderQuad = {x,y,tt.w,tt.h};

	if (tt.options & 1) {
		SDL_SetTextureColorMod(texture, tt.color.r, tt.color.g, tt.color.b);
	}
	if (tt.options & 2) {
		SDL_SetTextureAlphaMod(texture, tt.alpha);
	}
	if (tt.options & 4) {
		clipper = &tt.clip;
	}

	SDL_RenderCopyEx(mRenderer, texture, clipper, &renderQuad, tt.rotation, NULL, SDL_FLIP_NONE);

	if (tt.options & 1) {
		SDL_SetTextureColorMod(texture, 255, 255, 255);
	}
	if (tt.options & 2) {
		SDL_SetTextureAlphaMod(texture, 255);
	}
}
