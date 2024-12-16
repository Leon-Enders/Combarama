#include "AISystem.h"
#include <ctime>
#include <ranges>
#include "../GameObject/Character/Enemy.h"
#include "../../../Core/Math/Transform.h"
#include "World.h"


AISystem::AISystem(World* InGameWorld)
	:
	WorldSubsystem(InGameWorld)
{

}

void AISystem::Initialize()
{
	RandomGenerator = std::mt19937(static_cast<unsigned int>(std::time(nullptr)));
}

void AISystem::Update(float DeltaTime)
{

}

void AISystem::SpawnRandomEnemy()
{
	//TODO: Create viewport constant and it use here
	// Create distribution for width and height where enemies can spawn with some padding
	std::uniform_real_distribution<float> DistFloatWidth(50.f, 1100.f);
	std::uniform_real_distribution<float> DistFloatHeight(50.f, 600.f);

	Transform RandomSpawnTransform;
	RandomSpawnTransform.Position = { DistFloatWidth(RandomGenerator) , DistFloatHeight(RandomGenerator) };
	
	auto NewEnemyPtr = GetWorld()->SpawnGameObject<Enemy>(RandomSpawnTransform);
	std::weak_ptr<AIController> NewAIController = GetWorld()->SpawnGameObject<AIController>();

	NewAIController.lock()->PossessCharacter(std::shared_ptr<Enemy>(NewEnemyPtr));

	ActiveAIControllers.push_back(NewAIController);
}