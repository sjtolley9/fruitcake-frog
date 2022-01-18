#pragma once

#include "SDL.h"

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

