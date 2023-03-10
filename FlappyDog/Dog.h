#pragma once
#include <SDL_image.h>
#include "Game.h"
#include "GameObject.h"


class Dog : public GameObject
{
protected:

	std::vector<SDL_Texture*> textures;
	SDL_Rect position;

	double velocity;
	double gravity;
	double flightForce;

	int textureIndex;
	double lastTextureUpdateTime;

public:

	Dog();
	~Dog();

	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void Restart();

	void Flight();

	SDL_Rect* GetPosition();
};

