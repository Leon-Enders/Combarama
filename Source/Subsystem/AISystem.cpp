#include "AISystem.h"
#include <random>
#include <ctime>
#include <memory>
#include "../Math/Vector2.h"

AISystem::AISystem()
	:
	RandomGenerator(static_cast<unsigned int>(std::time(nullptr)))
{
}

void AISystem::Initialize(Character* TargetCharacter)
{
	for (int i = 0; i < 3; i++)
	{
		SpawnEnemy();
	}

	for (auto& ActiveAIController : AIControllers)
	{
		ActiveAIController.SetTarget(TargetCharacter);
	}
}

void AISystem::Update(float DeltaTime)
{
	for (auto& ActiveAIController : AIControllers)
	{
		ActiveAIController.MoveEnemy();
	}

	for (auto& ActiveEnemy : ActiveEnemies)
	{
		ActiveEnemy->Update(DeltaTime);
	}
}

void AISystem::Draw(SDL_Renderer* Renderer)
{
	for (auto& ActiveEnemy : ActiveEnemies)
	{
		ActiveEnemy->Draw(Renderer);
	}
}

void AISystem::SpawnEnemy()
{
	//TODO: Create viewport constant and it use here
	// Create distribution for width and height where enemies can spawn with some padding
	std::uniform_real_distribution<float> DistFloatWidth(50.f, 1100.f);
	std::uniform_real_distribution<float> DistFloatHeight(50.f, 600.f);


	Vector2 RandomSpawnPosition = { DistFloatWidth(RandomGenerator) , DistFloatHeight(RandomGenerator) };
	Enemy* NewEnemy = new Enemy(RandomSpawnPosition);
	NewEnemy->Initialize();

	ActiveEnemies.emplace_back(NewEnemy);

	AIControllers.emplace_back();
	AIControllers.back().PossessCharacter(ActiveEnemies.back());
}
