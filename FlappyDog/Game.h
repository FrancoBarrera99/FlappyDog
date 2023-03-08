#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <SDL_image.h>

class Dog;
class Level;
class Defs;
class ScoreWidget;
class Mix_Chunk;

class Game
{

private:

	static Game* gameInstance;

protected:

	bool running;
	bool paused;

	int score;

	SDL_Window* window;
	SDL_Renderer* renderer;

	Mix_Chunk* pointAudio;
	Mix_Chunk* endAudio;
	Mix_Chunk* flightAudio;


	Uint32 lastFrameTicks;
	Uint32 currentTicks;

	Level* level;
	Dog* dog;
	ScoreWidget* scoreWidget;

	double deltaTime;

	Game();
	~Game();

	bool Initialize();

	void HandleEvents(SDL_Event& event);

	void Update();

	void UpdateGameObjects();

	void UpdateUI();

	void Render();

	void RenderGameObjects();

	void RenderUI();


public:

	//Should not be clonable
	Game(Game& other) = delete;

	//Should not be asignable
	void operator=(const Game&) = delete;

	static Game* GetGameInstance();

	SDL_Renderer* GetRenderer() const;

	Dog* GetDog();

	int GetScore();

	void IncreaseScore();

	void EndGame();

	void Restart();

	void Run();
};