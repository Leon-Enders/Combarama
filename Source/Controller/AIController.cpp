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

void AIController::PossessCharacter(std::shared_ptr<Character> CharacterToPossess)
{
    ControlledEnemy = std::dynamic_pointer_cast<Enemy>(CharacterToPossess);


    if (auto SharedEnemyPtr = ControlledEnemy.lock())
    {
        SharedEnemyPtr->OnPossessed(this);

        StartPosition = SharedEnemyPtr->GetPosition();
        SharedEnemyPtr->UpdateVelocity({ 1.f,0.f });

        //Bind Unregistering + (temp) destruction of the controller to the destruction of the possessed character
        SharedEnemyPtr->OnDestroyDelegate = std::bind(&AIController::UnPossessCharacter, this);
    }
}

void AIController::Initialize()
{   
}

void AIController::CheckForTarget()
{
    if (IsPulled) return;

    if (auto SharedEnemyPtr = ControlledEnemy.lock())
    {
        auto PlayerCharacters = GetWorld()->GetAllActorsOfClass<PlayerCharacter>();

        for (const auto& PlayerChar : PlayerCharacters)
        {
            Vector2 DeltaPosition = PlayerChar->GetPosition() - SharedEnemyPtr->GetPosition();
            float Size = std::abs(DeltaPosition.Size());
            if (Size < PullRange)
            {
                IsPulled = true;
                Target = PlayerChar;
                SharedEnemyPtr->SetSpeed(275.f);
            }
        }
    }

   
}

void AIController::HandleAttackFrequency()
{
    if (Target.expired()) return;


    if (auto SharedEnemyPtr = ControlledEnemy.lock())
    {
        if (AttackTimer > 0)
        {
            AttackTimer--;
        }
        else
        {
            SharedEnemyPtr->Attack();
            AttackTimer = AttackResetTimer;
        }
    }
}

void AIController::UnPossessCharacter()
{
    ControlledEnemy.reset();

    //Temp solution: Remove from The world
    GetWorld()->RemoveController(this);
}

void AIController::MoveEnemy()
{
    if (auto SharedEnemyPtr = ControlledEnemy.lock())
    {
        if (auto SharedTargetPtr = Target.lock())
        {
            Vector2 DeltaPosition = SharedTargetPtr->GetPosition() - SharedEnemyPtr->GetPosition();
            Vector2 TargetDirection = DeltaPosition.Normalize();

            float LookAtRotation = std::atan2f(DeltaPosition.Y, DeltaPosition.X);

            SharedEnemyPtr->DesiredRotation = LookAtRotation;
            SharedEnemyPtr->UpdateVelocity(TargetDirection);
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

                SharedEnemyPtr->UpdateVelocity(NewVelocity);
            }
        }
    }
}

void AIController::RotateEnemy()
{

}


