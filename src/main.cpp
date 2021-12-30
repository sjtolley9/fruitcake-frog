/*	This example was sourced from:
	https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
	
	This was used to confirm that SDL2 was configured properly with CMake
*/

#include <iostream>
#include "SDL.h" 
#include "SDL_image.h"

SDL_Window *gWindow;
SDL_Renderer* gRenderer;

SDL_Rect gSpriteClips[ 40*31 ];

typedef struct frog_struct {
	float x;
	float y;
	float vx;
	float vy;
} frogGuy;

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL" << std::endl;
		success = false;
	} else {
		// Create SDL window
		gWindow = SDL_CreateWindow(
				"Fruitcake Frog",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				640,
				480,
				0
				);
		if (gWindow == NULL) {
			std::cout << "Window could not be created!" << std::endl;	
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if ( gRenderer == NULL ) {
				std::cout << "Failed to create renderer!" << std::endl;
				success = false;
			} else {
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255);

				int imgFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					std::cout << "SDL_image could not initialize" << std::endl;
					success = false;
				}
			}
		}
	}

	return success;
}

SDL_Texture* loadTexture( std::string path) {
	SDL_Texture* newTexture = NULL;
	
	SDL_Surface* loadedSurface = IMG_Load(path.c_str() );
	if ( loadedSurface == NULL ) {
		std::cout << "Unable to load image" << std::endl;
	} else {
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if (newTexture == NULL) {
			std::cout << "Unable to create texture" << std::endl;
		}
		
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

// Texture Wrapper Class
class LTexture {
	public:
		//Initializer
		LTexture();

		//Destructor
		~LTexture();

		//Loads image at path
		bool loadFromFile( std::string path );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

		//Gets image dimensions
		int getWidth();
		int getHeight();
	private:
		//Texture
		SDL_Texture* mTexture;

		//Dimensions
		int mWidth;
		int mHeight;
};

LTexture::LTexture() {
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path) {
	// Get rid of preexisting texture
	free();

	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 31; j++) {
			gSpriteClips[i + j*40].x = 16*i;
			gSpriteClips[i + j*40].y = 16*j;
			gSpriteClips[i + j*40].w = 16;
			gSpriteClips[i + j*40].h = 16;
		}
	}

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

void LTexture::render( int x, int y, SDL_Rect* clip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad);
}

int main(int argc, char *argv[])
{
	init();

	LTexture texture1;
	texture1.loadFromFile("assets/CL_DEMO.png");

	/*SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(
			"Fruitcake Frog",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640,
			480,
			0
			);*/

	

	Uint32 elapsedTime = 0, currentTime = SDL_GetTicks(), oldTime = SDL_GetTicks();

	bool playing = true;
	// For event handling
	SDL_Event e;

	while (playing) {
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - oldTime;
		oldTime = currentTime;

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				playing = false;
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
			}
		}

		// GAME LOGIC

		// RENDERING

		if (elapsedTime == 0) {
			SDL_RenderClear( gRenderer );

			for (int i = 0; i < 40; i++) {
				for (int j = 0; j < 31; j++) {
					texture1.render(17*i,17*j,&gSpriteClips[i+j*40]);
					//texture1.render(16*i,16*j,&gSpriteClips[13]);
				}
			}

			SDL_RenderPresent( gRenderer );
		}
	}

	SDL_DestroyWindow(gWindow);
	SDL_Quit();

	return 0;
}
