#include "Game.h"
#include "Dog.h"
#include "GameObject.h"
#include "Level.h"
#include "Defs.h"
#include "ScoreWidget.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <thread>

Game * Game::gameInstance = nullptr;
std::mutex Game::instanceMutex;

Game::Game() :
	window(nullptr), renderer(nullptr), running(false), paused(false), score(0), lastFrameTicks(0),
	currentTicks(0), deltaTime(0), dog(nullptr)
{
	running = Initialize();
}

Game::~Game()
{
	//Destroy Objects
	delete dog;
	delete level;
	delete scoreWidget;

	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Destroy audio
	Mix_FreeChunk(endAudio);
	Mix_FreeChunk(flightAudio);
	Mix_FreeChunk(pointAudio);

	//Quit SDL subsystems
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
}

Game* Game::GetGameInstance()
{
	std::lock_guard<std::mutex> lock(instanceMutex);

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
	Mix_PlayChannel(-1, pointAudio, 0);
	score += 1;
}

void Game::EndGame()
{
	Mix_PlayChannel(-1, endAudio, 0);
	paused = true;
}

void Game::Restart()
{
	score = 0;

	dog->Restart();
	level->Restart();
	scoreWidget->Restart();

	paused = false;
};

void Game::Run()
{
	//Create GameObjects
	dog = new Dog();
	level = new Level();

	//Create UI
	scoreWidget = new ScoreWidget();

	SDL_Event event;

	while (running)
	{
		HandleEvents(event);
		Update();
		Render();

		SDL_Delay(16);
	}
}

bool Game::Initialize()
{
	bool bSuccessfullyInitialized = true;

	/* -------------------VIDEO-----------------------*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_Video could not initialize: %s\n", SDL_GetError());
		return bSuccessfullyInitialized = false;
	}

	window = SDL_CreateWindow("Flappy Dog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

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

	/* -------------------IMAGE-----------------------*/
	int imgFlag = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlag) & imgFlag))
	{
		printf("SDL_Image could not initialize: %s\n", IMG_GetError());
		return bSuccessfullyInitialized = false;
	}

	/* -------------------TFF-----------------------*/
	if (TTF_Init() < 0)
	{
		printf("TTF could not initialize: %s\n", TTF_GetError());
		return bSuccessfullyInitialized = false;
	}

	/* -------------------AUDIO-----------------------*/
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL_Audio could not initialize: %s\n", SDL_GetError());
		return bSuccessfullyInitialized = false;
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//Load audio files
	pointAudio = Mix_LoadWAV("./Resources/Audio/PointAudio.wav");
	endAudio = Mix_LoadWAV("./Resources/Audio/EndAudio.wav");
	flightAudio = Mix_LoadWAV("./Resources/Audio/FlightAudio.wav");

	return bSuccessfullyInitialized;
}

void Game::HandleEvents(SDL_Event& event)
{
	if (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			running = false;
			return;
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !paused)
		{
			Mix_PlayChannel(-1, flightAudio, 0);
			dog->Flight();
			return;
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r && paused)
		{
			Restart();
			return;
		}
	}
}

void Game::Update()
{
	//Calculate deltaTime
	currentTicks = SDL_GetTicks64();
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
