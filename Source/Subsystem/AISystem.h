#pragma once
#include <vector>
#include "../Entity/Enemy.h"
#include "../Controller/AIController.h"
#include <random>


class Game;

//TODO: Make this a singleton and fix the ugly Initialize method, was only for testing purposes
//QUESTION: Should AIControllers own the enemies, since I want to destroy and spawn enemies but not the controllers?
class AISystem
{
public:
	AISystem();

	void Initialize(Character* TargetCharacter);
	void Update(float DeltaTime);
	

private:
	void SpawnEnemy();


	std::mt19937 RandomGenerator;
	std::vector<Enemy*> ActiveEnemies;
	std::vector<AIController> AIControllers;
};