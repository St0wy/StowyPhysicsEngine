#include <spdlog/spdlog.h>

#include "Game.hpp"

int main()
{
	spdlog::set_level(spdlog::level::debug);
	Game game;
	game.StartMainLoop();
}
