#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "FpsCounter.hpp"

#include "dynamics/DynamicsWorld.hpp"
#include "dynamics/Solver.hpp"

class DemoBallsAndCube
{
public:
	DemoBallsAndCube();
	void Run();

private:
	sf::RenderWindow _window;
	stw::DynamicsWorld _world;
	std::vector<std::unique_ptr<Entity>> _entities;
	std::unique_ptr<stw::ImpulseSolver> _impulseSolver;
	std::unique_ptr<stw::SmoothPositionSolver> _smoothPositionSolver;
	FpsCounter _fpsCounter;
	sf::Font _lModern;
	sf::Text _fpsText;
	sf::Vector2f _windowSize;
};
