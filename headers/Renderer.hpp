#ifndef FROG_RENDERER
#define FROG_RENDERER
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Renderer;

class TextureThing {
public:
	TextureThing();
	TextureThing(int, int, int);
	~TextureThing();

	void setColor(Uint8,Uint8,Uint8);
	void setAlpha(int);
	void setRotation(double);
	void setClip(SDL_Rect);

	int textureID;
	struct {
		Uint8 r;
		Uint8 g;
		Uint8 b;
	} color;
	double rotation;
	int alpha;
	int options;
	SDL_Rect clip;
	int w;
	int h;
};

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	bool init(Renderer*);
	void close();

	int createTexture(std::string path);

private:
	Renderer* mRenderer;
	//std::vector<LTexture*> textureCache;
	std::vector<SDL_Texture*> mTextureCache;
	friend class Renderer;
};

class Renderer {
public:
	Renderer();
	~Renderer();
	bool init();
	void close();

	void clearScreen();
	void presentScreen();

	void setFullscreen();
	void setScreenSize(int w, int h);

	void renderThing(TextureThing, int x, int y);

	TextureManager textureManager;
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;

	friend class TextureManager;
};

#endif
