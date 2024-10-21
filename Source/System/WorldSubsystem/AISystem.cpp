#include "AISystem.h"
#include <random>
#include <ctime>
#include <memory>
#include "../../Math/Transform.h"
#include "../../World/World.h"


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
	for (auto& ActiveAIController : ActiveAIControllers)
	{
		ActiveAIController->MoveEnemy();
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
	AIController* NewAIController = GetWorld()->CreateController<AIController>();

	NewAIController->PossessCharacter(NewEnemy);

	ActiveAIControllers.push_back(std::move(NewAIController));
}
