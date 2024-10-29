#include "AIController.h"
#include <ctime>
#include <chrono>
#include "../Entity/Enemy.h"
#include "../Math/ComboramaMath.h"
#include "../World/World.h"
#include "../System/WorldSubsystem/AISystem.h"
#include "../Utility/ComboramaTime.h"

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

    VelocityUpdateCounter++;

    if (VelocityUpdateCounter > VelocityMaxUpdateCounter)
    {
        VelocityUpdateCounter = 0;

        std::uniform_real_distribution<float> DistFloatWidth(-4.f, 4.f);
        std::uniform_real_distribution<float> DistFloatHeight(-4.f, 4.f);

       
       Vector2 NewVelocity = { DistFloatWidth(RandomGenerator::GetRandomEngine()) , DistFloatHeight(RandomGenerator::GetRandomEngine()) };

        ControlledEnemy->UpdateVelocity(NewVelocity);
    }
  
   
    
}


