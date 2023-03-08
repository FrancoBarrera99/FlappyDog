#pragma once
#include <SDL.h>


class GameObject
{

public:

	virtual ~GameObject() {};

	SDL_Renderer* renderer;

	virtual void Update(double deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Restart() = 0;
};

