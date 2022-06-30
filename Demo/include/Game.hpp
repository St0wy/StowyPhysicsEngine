#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();

	void StartMainLoop();

private:
	sf::RenderWindow _window;
};
