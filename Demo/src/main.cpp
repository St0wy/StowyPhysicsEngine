#include <spdlog/spdlog.h>

#include "DemoBalls.hpp"
#include "DemoBallsAndCube.hpp"

int main()
{
	spdlog::set_level(spdlog::level::debug);
	//DemoBalls game;
	DemoBallsAndCube game;
	game.StartMainLoop();
}
