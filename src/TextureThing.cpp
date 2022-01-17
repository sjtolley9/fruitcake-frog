#include "TextureThing.hpp"

TextureThing::TextureThing() {
	textureID = -1;
	color = {255, 255, 255};
	alpha = 255;
	options = 0;
}

TextureThing::~TextureThing() {
}

TextureThing::TextureThing(int id, int width, int height) {
	textureID = id;
	color = {255, 255, 255};
	alpha = 255;
	options = 0;
	w = width;
	h = height;
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