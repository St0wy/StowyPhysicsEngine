#include <spdlog/spdlog.h>

#include "DemoBalls.hpp"
#include "DemoBallsAndCube.hpp"
#include "DemoGjk.hpp"

int main()
{
	spdlog::set_level(spdlog::level::debug);

	//DemoBalls game;
	DemoBallsAndCube game;
	//DemoGjk game;
	game.StartMainLoop();
}
