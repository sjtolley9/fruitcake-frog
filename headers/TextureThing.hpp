#pragma once

#include "SDL.h"

class TextureThing {
public:
	TextureThing();
	TextureThing(int, int, int);
	~TextureThing();

	void setColor(int,int,int);
	void setAlpha(int);
	void setRotation(double);
	void setClip(SDL_Rect);

	int textureID;
	struct {
		int r;
		int g;
		int b;
	} color;
	double rotation;
	int alpha;
	int options;
	SDL_Rect clip;
	int w;
	int h;
};