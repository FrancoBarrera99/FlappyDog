#include "ScoreWidget.h"
#include "Game.h"
#include "Defs.h"

ScoreWidget::ScoreWidget():
	position({(SCREEN_WIDTH/2 - SCORE_WIDTH/2), 30, SCORE_HEIGHT, SCORE_WIDTH}), textTexture(nullptr)
{
	renderer = Game::GetGameInstance()->GetRenderer();
	font = TTF_OpenFont("./Resources/Fonts/Expo-Bold.otf", 50);
	
	Update();
}

ScoreWidget::~ScoreWidget()
{
	SDL_DestroyTexture(textTexture);
}

void ScoreWidget::Update()
{
	int score = Game::GetGameInstance()->GetScore();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), { 255, 255, 255, 255 });

	if (textTexture != nullptr)
	{
		SDL_DestroyTexture(textTexture);
	}

	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
}

void ScoreWidget::Render()
{
	SDL_RenderCopy(renderer, textTexture, nullptr, &position);
}

void ScoreWidget::Restart()
{
	Update();
	Render();
}
