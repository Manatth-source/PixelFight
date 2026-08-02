#include "Game/Game.h"
#include "Utils/Logger.h"


 int main(void) 
 {
	std::ofstream logFile("game.log");
	Logger::setStream(logFile);

	Game game;
	game.run();

	return 0;
}