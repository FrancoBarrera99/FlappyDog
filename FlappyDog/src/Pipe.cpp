#include "Pipe.h"
#include "Game.h"
#include "Dog.h"
#include "Defs.h"

Pipe::Pipe() :
	velocity(200), positionX(0), positionY(0), randomMin(0), randomMax(0), textureHeight(PIPE_HEIGHT), textureWidth(PIPE_WIDTH), pipeGap(100),
	topPosition({ 0,0,0,0 }), botPosition({0,0,0,0}), scoreUpdated(false)
{
	renderer = Game::GetGameInstance()->GetRenderer();

	textureTop = IMG_LoadTexture(renderer, "./Resources/Textures/TopPipe.png");
	textureBot = IMG_LoadTexture(renderer, "./Resources/Textures/BotPipe.png");

	positionX = SCREEN_WIDTH;

	//Random Y position
	randomMin = static_cast<int>(SCREEN_HEIGHT / 4);
	randomMax = randomMin * 3;

	positionY = rand() % (randomMax - randomMin + 1) + randomMin;
}

Pipe::~Pipe()
{
	SDL_DestroyTexture(textureBot);
	SDL_DestroyTexture(textureTop);
}

void Pipe::Update(double deltaTime)
{
	int increment = static_cast<int>(velocity * deltaTime);

	if (positionX <= -textureWidth) 
	{
		RestartPosition();
	}
	else {
		positionX -= increment;
	}

	SDL_Rect* DogPosition = Game::GetGameInstance()->GetDog()->GetPosition();

	if (isColliding(DogPosition))
	{
		Game::GetGameInstance()->EndGame();
	}

	if (isPointReached(DogPosition) && !scoreUpdated) {
		Game::GetGameInstance()->IncreaseScore();
		scoreUpdated = true;
	}
}

void Pipe::Render()
{
	topPosition = { positionX, positionY - pipeGap - textureHeight, textureWidth, textureHeight };
	SDL_RenderCopy(renderer, textureTop, nullptr, &topPosition);

	botPosition = { positionX, positionY + pipeGap, textureWidth, textureHeight };
	SDL_RenderCopy(renderer, textureBot, nullptr, &botPosition);
}

void Pipe::Restart()
{
	RestartPosition();
}

void Pipe::RestartPosition()
{
	positionX = SCREEN_WIDTH;
	positionY = rand() % (randomMax - randomMin + 1) + randomMin;
	scoreUpdated = false;
}

int Pipe::GetPositionX()
{
	return positionX;
}

bool Pipe::isColliding(SDL_Rect* position)
{
	return (SDL_HasIntersection(position, &botPosition) || SDL_HasIntersection(position, &topPosition));
}

bool Pipe::isPointReached(SDL_Rect* position)
{
	return position->x > positionX + textureWidth;
}
