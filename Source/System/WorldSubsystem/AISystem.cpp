#include "AISystem.h"
#include <random>
#include <ctime>
#include <memory>
#include "../../Math/Transform.h"
#include "../../World/World.h"


void AISystem::Initialize(World* InGameWorld)
{
	WorldSubsystem::Initialize(InGameWorld);

	
	RandomGenerator = std::mt19937(static_cast<unsigned int>(std::time(nullptr)));

}

void AISystem::Update(float DeltaTime)
{
	for (auto& ActiveAIController : ActiveAIControllers)
	{
		ActiveAIController->MoveEnemy();
	}

	for (auto& ActiveEnemy : ActiveEnemies)
	{
		ActiveEnemy->Update(DeltaTime);
	}
}

void AISystem::SpawnRandomEnemy()
{
	//TODO: Create viewport constant and it use here
	// Create distribution for width and height where enemies can spawn with some padding
	std::uniform_real_distribution<float> DistFloatWidth(50.f, 1100.f);
	std::uniform_real_distribution<float> DistFloatHeight(50.f, 600.f);

	Transform RandomSpawnTransform;
	RandomSpawnTransform.Position = { DistFloatWidth(RandomGenerator) , DistFloatHeight(RandomGenerator) };
	
	Enemy* NewEnemy = GetWorld()->SpawnActor<Enemy>(RandomSpawnTransform);
	ActiveEnemies.push_back(std::move(NewEnemy));

	AIController* NewAIController = GetWorld()->CreateController<AIController>();
	ActiveAIControllers.push_back(std::move(NewAIController));
}
