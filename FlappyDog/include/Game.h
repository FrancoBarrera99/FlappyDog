#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <SDL_image.h>
#include <mutex>
#include <queue>
#include <condition_variable>

class Dog;
class Level;
class Defs;
class ScoreWidget;
class Mix_Chunk;

class Game
{

private:

	static Game* gameInstance;
	static std::mutex instanceMutex;

protected:

	bool running;
	bool paused;
	int score;
	Uint32 lastFrameTicks;
	Uint32 currentTicks;
	double deltaTime;

	SDL_Window* window;
	SDL_Renderer* renderer;

	Mix_Chunk* pointAudio;
	Mix_Chunk* endAudio;
	Mix_Chunk* flightAudio;

	Level* level;
	Dog* dog;
	ScoreWidget* scoreWidget;


	std::queue<SDL_Event> eventsQueue;
	std::mutex eventsMutex;
	std::condition_variable cvDraw;

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