#pragma once
#include <SDL_image.h>
#include <string>
#include "GameObject.h"


class Pipe : public GameObject
{
protected:

	SDL_Texture* textureBot;
	SDL_Texture* textureTop;
	SDL_Rect botPosition;
	SDL_Rect topPosition;

	double velocity;
	int textureHeight, 
		textureWidth,
		positionX,
		positionY,
		pipeGap,
		randomMin, 
		randomMax;
	bool scoreUpdated;

public:

	Pipe();
	~Pipe();

	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void Restart();

	void RestartPosition();

	int GetPositionX();	

	bool isColliding(SDL_Rect* position);
	bool isPointReached(SDL_Rect* position);

};

