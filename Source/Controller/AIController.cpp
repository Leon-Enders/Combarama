#include "AIController.h"
#include "../Entity/Enemy.h"
#include "../Math/ComboramaMath.h"

AIController::AIController()
{

}

void AIController::Initialize()
{

}

void AIController::SetTarget(Character* TargetCharacter)
{
    Target = TargetCharacter;
}

void AIController::PossessCharacter(Character* CharacterToPossess)
{
    Enemy* EnemyToPossess = static_cast<Enemy*>(CharacterToPossess);

    if (EnemyToPossess)
    {
        ControlledEnemy = EnemyToPossess;
        ControlledEnemy->OnPossessed(this);
    }

    StartPosition = ControlledEnemy->GetPosition();
    ControlledEnemy->UpdateVelocity({ 1.f,0.f });
}

void AIController::MoveEnemy()
{
    if (!ControlledEnemy) return;
    if (ControlledEnemy->GetPosition().X > StartPosition.X + MaxXDistance)
    {
        ControlledEnemy->UpdateVelocity({-1.f,0.f});
    }
    if (ControlledEnemy->GetPosition().X < StartPosition.X - MaxXDistance)
    {
        ControlledEnemy->UpdateVelocity({ 1.f,0.f });
    }
}


