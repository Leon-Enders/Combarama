#include "AIController.h"
#include "../Entity/Enemy.h"

AIController::AIController()
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
        ControlledEnemy = std::unique_ptr<Enemy>(EnemyToPossess);

        
        ControlledEnemy->OnPossessed(this);
    }
}

void AIController::MoveEnemy()
{
    if (!Target || !ControlledEnemy) return;
    float DeltaX = Target->GetPosition().X - ControlledEnemy->GetPosition().X;
    float DeltaY = Target->GetPosition().Y - ControlledEnemy->GetPosition().Y;

    Vector2 TargetDelta = { DeltaX , DeltaY };
    Vector2 TargetDirection = TargetDelta.Normalize();


    ControlledEnemy->UpdateVelocity(TargetDirection);
}

void AIController::Initialize()
{

}
