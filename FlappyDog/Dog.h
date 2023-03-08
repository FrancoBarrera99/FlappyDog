#pragma once
#include <SDL_image.h>
#include "Game.h"
#include "GameObject.h"


class Dog : public GameObject
{
protected:

	SDL_Texture* texture;
	SDL_Rect position;
	double velocity;
	double gravity;
	double flightForce;

public:

	Dog();
	~Dog();

	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void Restart();

	void Flight();

	SDL_Rect* GetPosition();
};

