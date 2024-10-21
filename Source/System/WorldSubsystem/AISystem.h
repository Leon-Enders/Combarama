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
	virtual void Initialize(World* InGameWorld);
	virtual void Update(float DeltaTime);
	void SpawnRandomEnemy();

private:

	std::mt19937 RandomGenerator;
	std::vector<Enemy*> ActiveEnemies;
	std::vector<AIController*> ActiveAIControllers;
};