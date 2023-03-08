#include "Level.h"
#include "Game.h"
#include "Pipe.h"
#include "Defs.h"

Level::Level()
{
	renderer = Game::GetGameInstance()->GetRenderer();

	backgroundTexture = IMG_LoadTexture(renderer, "./Resources/Textures/Background.png");

	pipes.push_back(new Pipe());
	pipes.push_back(new Pipe());
	pipes.push_back(new Pipe());

	pipesIndex = 1;
	pipesGap = (SCREEN_WIDTH + PIPE_WIDTH)/ pipes.size();
}

Level::~Level()
{
	SDL_DestroyTexture(backgroundTexture);
}

void Level::Update(double deltaTime)
{
	//Check if current pipe position exceed pipes gap limit
	if ((pipes[pipesIndex - 1]->GetPositionX() < SCREEN_WIDTH - pipesGap) && (pipesIndex < pipes.size())) {
		//Add next pipe to update cycle
		pipesIndex += 1;
	}
	
	for(int i = 0; i < pipesIndex; i++)
	{
		pipes[i]->Update(deltaTime);
	}

}

void Level::Render()
{
	SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
	for (Pipe* pipe : pipes)
	{
		pipe->Render();
	}
}

void Level::Restart()
{
	for (Pipe* pipe : pipes) {
		pipe->Restart();
	}

	pipesIndex = 1;
}
