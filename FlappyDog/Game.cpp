#include "Game.h"
#include "Dog.h"
#include "GameObject.h"
#include "Level.h"
#include "Defs.h"
#include "ScoreWidget.h"
#include <SDL_ttf.h>


Game* Game::gameInstance = nullptr;

Game::Game() :
	window(nullptr), renderer(nullptr), running(false), paused(false), score(0), lastFrameTicks(0),
	currentTicks(0), deltaTime(0),dog(nullptr)
{
	running = Initialize();
}

Game::~Game() 
{
	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

Game* Game::GetGameInstance()
{
	if (gameInstance == nullptr)
	{
		gameInstance = new Game();
	}
	return gameInstance;
}

SDL_Renderer* Game::GetRenderer() const {
	return renderer;
}

Dog* Game::GetDog() {
	return dog;
}
int Game::GetScore()
{
	return score;
}
void Game::IncreaseScore()
{
	score += 1;
}
void Game::EndGame()
{
	paused = true;

	//show restart UI
}
void Game::Restart()
{
	score = 0;

	dog->Restart();
	level->Restart();
	scoreWidget->Restart();

	//hide restart UI

	paused = false;
};

void Game::Run()
{
	SDL_Event event;

	//Create GameObjects
	dog = new Dog();
	level = new Level();

	//Create UI
	scoreWidget = new ScoreWidget();

	while (running)
	{
		HandleEvents(event);
		Update();
		Render();

		SDL_Delay(12);
	}
}

bool Game::Initialize()
{
	bool bSuccessfullyInitialized = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize: %s\n", SDL_GetError());
		return bSuccessfullyInitialized = false;
	}
	
	window = SDL_CreateWindow("Flappy Dog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
			printf("Window could not be created: %s\n", SDL_GetError());
			return bSuccessfullyInitialized = false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		printf("Renderer could not be created: %s\n", SDL_GetError());
		return bSuccessfullyInitialized = false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlag = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlag) & imgFlag))
	{
		printf("SDL_Image could not initialize: %s\n", IMG_GetError());
		return bSuccessfullyInitialized = false;
	}

	if (TTF_Init() < 0) 
	{
		printf("TTF could not initialize: %s\n", TTF_GetError());
		return bSuccessfullyInitialized = false;
	}

	return bSuccessfullyInitialized;
}

void Game::HandleEvents(SDL_Event& event)
{
	if (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;

		case SDL_KEYDOWN:
			
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				dog->Flight();
				break;

			case SDLK_r:
				if (paused) {
					Restart();
				}
			default:
				break;
			}


			break;

		default:
			break;
		}
	}
}

void Game::Update()
{
	//Calculate deltaTime
	currentTicks = SDL_GetTicks();
	deltaTime = (currentTicks - lastFrameTicks) / 1000.0f;
	lastFrameTicks = currentTicks;

	UpdateGameObjects();
	UpdateUI();
}

void Game::UpdateGameObjects()
{
	if (!paused)
	{
		level->Update(deltaTime);
		dog->Update(deltaTime);
	}
}

void Game::UpdateUI()
{
	scoreWidget->Update();
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	RenderGameObjects();
	RenderUI();

	SDL_RenderPresent(renderer);
}

void Game::RenderGameObjects()
{
	level->Render();
	dog->Render();
}

void Game::RenderUI()
{
	scoreWidget->Render();
}

