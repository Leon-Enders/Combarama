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

void AIController::Update(float DeltaTime)
{
    CheckForTarget();
    MoveEnemy();
    RotateEnemy();
    HandleAttackFrequency();
   
}

void AIController::Initialize()
{   
}

void AIController::CheckForTarget()
{
    if (!ControlledEnemy || IsPulled) return;

    auto PlayerCharacters = GetWorld()->GetAllActorsOfClass<PlayerCharacter>();

    for (const auto& PlayerChar : PlayerCharacters)
    {
        Vector2 DeltaPosition = PlayerChar.get().GetPosition() - ControlledEnemy->GetPosition();
        float Size = std::abs(DeltaPosition.Size());
        if (Size < PullRange)
        {
            IsPulled = true;
            Target = &PlayerChar.get();
        }
    }
}

void AIController::HandleAttackFrequency()
{
    if (Target && ControlledEnemy)
    {
        if (AttackTimer > 0)
        {
            AttackTimer--;
        }
        else
        {
            ControlledEnemy->Attack();
            AttackTimer = AttackResetTimer;
        }
    }
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


    if (Target)
    {
        Vector2 DeltaPosition = Target->GetPosition() - ControlledEnemy->GetPosition();
        Vector2 TargetDirection = DeltaPosition.Normalize();

        float LookAtRotation = std::atan2f(DeltaPosition.Y, DeltaPosition.X);

        ControlledEnemy->DesiredRotation = LookAtRotation;
        ControlledEnemy->UpdateVelocity(TargetDirection);
    }
    else
    {

        VelocityUpdateCounter++;

        if (VelocityUpdateCounter > VelocityMaxUpdateCounter)
        {
            VelocityUpdateCounter = 0;

            std::uniform_real_distribution<float> DistFloatWidth(-1.f, 1.f);
            std::uniform_real_distribution<float> DistFloatHeight(-1.f, 1.f);


            Vector2 NewVelocity = { DistFloatWidth(RandomGenerator::GetRandomEngine()) , DistFloatHeight(RandomGenerator::GetRandomEngine()) };

            ControlledEnemy->UpdateVelocity(NewVelocity);
        }
    }
}

void AIController::RotateEnemy()
{

}


