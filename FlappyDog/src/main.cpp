#include <ctime>
#include "Game.h"


int main(int argc, char* argv[]) 
{
	srand(time(nullptr));

	Game::GetGameInstance()->Run();

	return 0;
}