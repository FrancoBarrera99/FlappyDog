#pragma once
#include <SDL.h>
#include <SDL_ttf.h>


class ScoreWidget
{
protected:

	TTF_Font* font;
	SDL_Renderer* renderer;
	SDL_Texture* textTexture;
	SDL_Rect position;

public:

	ScoreWidget();
	~ScoreWidget();

	virtual void Update();
	virtual void Render();
	virtual void Restart();

};

