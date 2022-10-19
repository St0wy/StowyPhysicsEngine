#include "DemoBallsAndCube.hpp"

#include <format>
#include <iostream>

#include "AabbBox.hpp"
#include "Circle.hpp"
#include "Consts.hpp"
#include "FpsCounter.hpp"
#include "MathUtils.hpp"

#include "math/Vector2.hpp"

DemoBallsAndCube::DemoBallsAndCube()
	: _window(
	sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
	WINDOW_NAME,
	sf::Style::Close,
	sf::ContextSettings(0, 0, 8)
	)
{
	_window.setView(DEFAULT_VIEW);

	_impulseSolver = std::make_unique<stw::ImpulseSolver>();
	_smoothPositionSolver = std::make_unique<stw::SmoothPositionSolver>();
	_world.AddSolver(_impulseSolver.get());
	_world.AddSolver(_smoothPositionSolver.get());

	if (!_lModern.loadFromFile("data/lmodern.otf"))
	{
		std::cerr << "Could not load font\n";
	}

	_fpsText.setFont(_lModern);
	_fpsText.setCharacterSize(256);
	_fpsText.setFillColor(sf::Color::White);
	_fpsText.setPosition(-CAM_WIDTH / 2.0f, -CAM_HEIGHT / 2.0f);
	_fpsText.setScale(0.01f, 0.01f);
}

void DemoBallsAndCube::Run()
{
	constexpr bool everyFrame = false;
	auto ground = std::make_unique<AabbBox>(
		_world,
		stw::Vector2(CAM_WIDTH * 0.8f, CAM_HEIGHT * 0.05f),
		stw::Vector2(0.0f, CAM_HEIGHT * -0.3f),
		false
		);
	ground->RigidBody()->SetIsKinematic(false);
	ground->RigidBody()->SetTakesGravity(false);
	ground->RigidBody()->SetMass(std::numeric_limits<float>::max());
	//ground->RigidBody()->SetMass(300000000000000000000000000000000000000.0f);
	_entities.push_back(std::move(ground));

	std::cout << "Starting main loop\n";

	sf::Clock clock;
	bool isMousePressed = false;
	while (_window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		sf::Event event{};
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				isMousePressed = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				isMousePressed = false;
			}
		}

		if (isMousePressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				auto posi = sf::Mouse::getPosition(_window);
				auto posf = _window.mapPixelToCoords(posi);
				auto physicsPos = SfmlPosToSpe(posf);
				std::cout << "Spawn pos : " << physicsPos << "\n";
				_entities.push_back(
					std::make_unique<Circle>(_world, 1.0f, physicsPos));
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				auto posi = sf::Mouse::getPosition(_window);
				auto posf = _window.mapPixelToCoords(posi);
				auto physicsPos = SfmlPosToSpe(posf);
				std::cout << "Spawn pos : " << physicsPos << "\n";
				_entities.push_back(
					std::make_unique<AabbBox>(_world, stw::Vector2(2.f, 2.f), physicsPos, true));
			}

			if constexpr (!everyFrame)
				isMousePressed = false;
		}

		// Step the physics
		_world.Step(deltaTime.asSeconds());

		// Update the entites
		for (const auto& entity : _entities)
		{
			entity->Update(deltaTime);
		}

		_fpsCounter.Update(deltaTime.asSeconds());
		_fpsText.setString(_fpsCounter.GetFpsString());

		// Clear the window
		_window.clear(sf::Color::Black);

		// Render all the entities
		for (const auto& entity : _entities)
		{
			_window.draw(*entity);
		}

		_window.draw(_fpsText);

		_window.display();
	}
}
