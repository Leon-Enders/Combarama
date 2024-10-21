#pragma once
#include <vector>
#include "WorldSubsystem.h"
#include "../../Entity/Enemy.h"
#include "../../Controller/AIController.h"
#include <random>


class Game;

class AISystem : public WorldSubsystem
{
public:
	AISystem(World* InGameWorld);
	virtual void Initialize();
	virtual void Update(float DeltaTime);
	void SpawnRandomEnemy();

private:

	std::mt19937 RandomGenerator;
	std::vector<AIController*> ActiveAIControllers;
};