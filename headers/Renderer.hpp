#ifndef FROG_RENDERER
#define FROG_RENDERER
#include "SDL_image.h"
#include "SDL_ttf.h"

class Renderer {
public:
	Renderer();
	~Renderer();
	bool init();
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;
};

#endif
