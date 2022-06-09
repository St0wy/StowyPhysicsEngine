#include "Game.h"

#include <spdlog/spdlog.h>

#include "Consts.h"

Game::Game()
	: _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close)
{
	_window.setVerticalSyncEnabled(false);
}

void Game::StartMainLoop()
{
	spdlog::debug("Starting main loop");

	sf::Clock clock;
	while (_window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		sf::Event event{};

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
		}

		// Clear the window
		_window.clear(sf::Color::Black);

		_window.display();
	}
}
