#pragma once
#include <vector>
#include "../Entity/Enemy.h"
#include "../Controller/AIController.h"
#include <random>


class Game;

//QUESTION: Should AIControllers own the enemies, since I want to destroy and spawn enemies but not the controllers?
class AISystem
{
public:
	AISystem();

	void Initialize(Character* TargetCharacter);
	void Update(float DeltaTime);

	void Draw(SDL_Renderer* Renderer);
	

private:
	void SpawnEnemy();


	std::mt19937 RandomGenerator;
	std::vector<Enemy*> ActiveEnemies;
	std::vector<AIController> AIControllers;
};