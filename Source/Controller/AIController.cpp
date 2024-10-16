#include "AIController.h"
#include "../Entity/Enemy.h"

AIController::AIController()
{

}

void AIController::PossessCharacter(Character* CharacterToPossess)
{
    Enemy* EnemyToPossess = static_cast<Enemy*>(CharacterToPossess);

    if (EnemyToPossess)
    {
        ControlledEnemy = std::unique_ptr<Enemy>(EnemyToPossess);

        
        ControlledEnemy->OnPossessed(this);
    }
}

void AIController::Initialize()
{

}
