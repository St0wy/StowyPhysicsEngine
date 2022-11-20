#include <benchmark/benchmark.h>
#include "dynamics/DynamicsWorld.hpp"
#include "dynamics/Solver.hpp"
#include "Entity.hpp"
#include "AabbBox.hpp"
#include "Circle.hpp"

static constexpr int ITERATION_COUNT = 1000;
static constexpr float DELTA_TIME = 1.0f / 50.0f;

static void BM_CollisionsGrid(benchmark::State& state)
{
	for (auto _ : state)
	{
		stw::DynamicsWorld world;
		world.useSpacePartitioning = true;

		auto impulseSolver = std::make_unique<stw::ImpulseSolver>();
		auto smoothPositionSolver = std::make_unique<stw::SmoothPositionSolver>();
		world.AddSolver(impulseSolver.get());
		world.AddSolver(smoothPositionSolver.get());

		std::vector<std::unique_ptr<Entity>> entities;

		auto ground = std::make_unique<AabbBox>(
			world,
			stw::Vector2(100.0f, 1.0f),
			stw::Vector2(0.0f, -0.3f),
			false);
		ground->RigidBody()->SetIsKinematic(false);
		ground->RigidBody()->SetTakesGravity(false);
		ground->RigidBody()->SetMass(std::numeric_limits<float>::max());
		entities.push_back(std::move(ground));

		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				entities.push_back(std::make_unique<Circle>(world, 0.9f,
					stw::Vector2{ static_cast<float>(i), static_cast<float>(j) + 30.0f }));

			}
		}

		for (int i = 0; i < ITERATION_COUNT; ++i)
		{
			world.Step(DELTA_TIME);
		}
	}
}
BENCHMARK(BM_CollisionsGrid);

static void BM_CollisionsNoGrid(benchmark::State& state)
{
	for (auto _ : state)
	{
		stw::DynamicsWorld world;
		world.useSpacePartitioning = false;

		auto impulseSolver = std::make_unique<stw::ImpulseSolver>();
		auto smoothPositionSolver = std::make_unique<stw::SmoothPositionSolver>();
		world.AddSolver(impulseSolver.get());
		world.AddSolver(smoothPositionSolver.get());

		std::vector<std::unique_ptr<Entity>> entities;

		auto ground = std::make_unique<AabbBox>(
			world,
			stw::Vector2(100.0f, 1.0f),
			stw::Vector2(0.0f, -0.3f),
			false);
		ground->RigidBody()->SetIsKinematic(false);
		ground->RigidBody()->SetTakesGravity(false);
		ground->RigidBody()->SetMass(std::numeric_limits<float>::max());
		entities.push_back(std::move(ground));

		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				entities.push_back(std::make_unique<Circle>(world, 0.9f,
					stw::Vector2{ static_cast<float>(i), static_cast<float>(j) + 30.0f }));

			}
		}

		for (int i = 0; i < ITERATION_COUNT; ++i)
		{
			world.Step(DELTA_TIME);
		}
	}
}
BENCHMARK(BM_CollisionsNoGrid);

BENCHMARK_MAIN();