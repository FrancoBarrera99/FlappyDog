#pragma once
#include <vector>
#include <string>
#include <SDL_image.h>
#include "GameObject.h"

class Pipe;

class Level : public GameObject
{
private:

	SDL_Texture* backgroundTexture;
	std::vector<Pipe*> pipes;

	int pipesIndex,
		pipesGap;

public:
	Level();
	~Level();

	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void Restart();

};

