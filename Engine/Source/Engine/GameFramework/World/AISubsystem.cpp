#include "AISubsystem.h"
#include <ctime>
#include <ranges>
#include "../GameObject/Character/Enemy.h"
#include "../../../Core/Math/Transform.h"
#include "../../../Core/Misc/CombaramaConstants.h"
#include "World.h"


AISubsystem::AISubsystem(World* GameWorld)
	:
	WorldSubsystem(GameWorld)
{

}

void AISubsystem::Initialize()
{
	RandomGenerator = std::mt19937(static_cast<unsigned int>(std::time(nullptr)));
}

void AISubsystem::SpawnRandomEnemy()
{

	std::uniform_real_distribution<float> DistFloatWidth(-800.f, 800.f);
	std::uniform_real_distribution<float> DistFloatHeight(-800.f, 800.f);

	Transform RandomSpawnTransform;
	RandomSpawnTransform.Position = { DistFloatWidth(RandomGenerator) , DistFloatHeight(RandomGenerator) };
	
	auto NewEnemyPtr = GetWorld()->SpawnGameObject<Enemy>(RandomSpawnTransform);
	std::weak_ptr<AIController> NewAIController = GetWorld()->SpawnGameObject<AIController>();

	NewAIController.lock()->PossessCharacter(std::shared_ptr<Enemy>(NewEnemyPtr));

	ActiveAIControllers.push_back(NewAIController);
}