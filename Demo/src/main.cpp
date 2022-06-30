#include <spdlog/spdlog.h>

#include "DemoBalls.hpp"

int main()
{
	spdlog::set_level(spdlog::level::debug);
	DemoBalls game;
	game.StartMainLoop();
}
