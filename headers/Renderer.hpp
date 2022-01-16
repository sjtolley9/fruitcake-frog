#ifndef FROG_RENDERER
#define FROG_RENDERER
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Renderer;

//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture();
		LTexture( SDL_Renderer*, SDL_Texture*, int w, int h);

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path );
        
        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;
		SDL_Renderer* mRenderer;

        //Image dimensions
        int mWidth;
        int mHeight;
};

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	bool init(Renderer*);
	void close();

	LTexture createTexture(std::string path);

private:
	Renderer* mRenderer;
};

class Renderer {
public:
	Renderer();
	~Renderer();
	bool init();
	void close();

	void clearScreen();
	void presentScreen();
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;

	friend class TextureManager;
};

#endif
