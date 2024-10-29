#include "AIController.h"
#include "../Entity/Enemy.h"
#include "../Math/ComboramaMath.h"
#include "../World/World.h"
#include "../System/WorldSubsystem/AISystem.h"

AIController::AIController(World* InOwningWorld)
    :
    Controller(InOwningWorld)
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


    //Bind Unregistering + (temp) destruction of the controller to the destruction of the possessed character
    ControlledEnemy->OnDestroyDelegate = std::bind(&AIController::UnPossessCharacter, this);
}

void AIController::UnPossessCharacter()
{
    //Unregister from the subsystem
    GetWorld()->GetSubsystem<AISystem>()->RemoveAIController(*this);
    ControlledEnemy = nullptr;

    //Temp solution: Remove from The world
    GetWorld()->RemoveController(this);
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


