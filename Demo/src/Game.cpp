#include "Game.hpp"

#include <spdlog/spdlog.h>

#include "Consts.hpp"
#include "Sphere.hpp"

Game::Game()
	: _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close)
{
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(FRAMERATE);

	_window.setView(DEFAULT_VIEW);

	_impulseSolver = std::make_unique<ImpulseSolver>();
	_smoothPositionSolver = std::make_unique<SmoothPositionSolver>();
	_world.AddSolver(_impulseSolver.get());
	_world.AddSolver(_smoothPositionSolver.get());
	_world.SetWorldGravity({ 0,0 });
}

void Game::StartMainLoop()
{
	_entities.push_back(
		std::make_unique<Sphere>(_world, 1.0f, sf::Vector2f(-3.0f, 3.0f)));
	_entities.push_back(
		std::make_unique<Sphere>(_world, 1.0f, sf::Vector2f(0.0f, 3.0f)));
	_entities.push_back(
		std::make_unique<Sphere>(_world, 1.0f, sf::Vector2f(3.0f, 3.0f)));


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

		// Step the physics
		_world.Step(deltaTime.asSeconds());

		// Update the entites
		for (const auto& entity : _entities)
		{
			entity->Update(deltaTime);
		}

		_entities[_entities.size() - 1]->Push(sf::Vector2f(-2.0f, 0.f));

		// Clear the window
		_window.clear(sf::Color::Black);

		// Render all the entities
		for (const auto& entity : _entities)
		{
			_window.draw(*entity);
		}

		_window.display();
	}
}
