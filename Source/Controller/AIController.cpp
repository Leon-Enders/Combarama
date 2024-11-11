#include "AIController.h"
#include <ctime>
#include <chrono>
#include "../Entity/Enemy.h"
#include "../Math/ComboramaMath.h"
#include "../World/World.h"
#include "../System/WorldSubsystem/AISystem.h"
#include "../Utility/ComboramaTime.h"
#include "../Coroutine/CoroutineManager.h"

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


    if (auto sEnemyPtr = ControlledEnemy.lock())
    {
        sEnemyPtr->OnPossessed(this);

        StartPosition = sEnemyPtr->GetPosition();
        sEnemyPtr->UpdateVelocity({ 1.f,0.f });

        //Bind Unregistering + (temp) destruction of the controller to the destruction of the possessed character
        sEnemyPtr->OnDestroyDelegate.AddMemberFunction(shared_from_this(), &AIController::UnPossessCharacter);
    }
}

void AIController::Initialize()
{   
}

void AIController::CheckForTarget()
{
    if (IsPulled) return;

    if (auto sEnemyPtr = ControlledEnemy.lock())
    {
        auto PlayerCharacters = GetWorld()->GetAllActorsOfClass<PlayerCharacter>();

        for (const auto& PlayerChar : PlayerCharacters)
        {
            Vector2 DeltaPosition = PlayerChar->GetPosition() - sEnemyPtr->GetPosition();
            float Size = std::abs(DeltaPosition.Size());
            if (Size < PullRange)
            {
                IsPulled = true;
                Target = PlayerChar;
                sEnemyPtr->SetSpeed(275.f);
            }
        }
    }

   
}

void AIController::HandleAttackFrequency()
{
    if (Target.expired()) return;


    if (auto sEnemyPtr = ControlledEnemy.lock())
    {
        if (CanAttack)
        {
            CoroutineManager::Get().StartCoroutine(ActivateAttackCooldown());
            sEnemyPtr->Attack();
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
    if (auto sEnemyPtr = ControlledEnemy.lock())
    {
        if (auto sTargetPtr = Target.lock())
        {
            Vector2 DeltaPosition = sTargetPtr->GetPosition() - sEnemyPtr->GetPosition();
            Vector2 TargetDirection = DeltaPosition.Normalize();

            float LookAtRotation = std::atan2f(DeltaPosition.Y, DeltaPosition.X);

            sEnemyPtr->DesiredRotation = LookAtRotation;
            sEnemyPtr->UpdateVelocity(TargetDirection);
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

                sEnemyPtr->UpdateVelocity(NewVelocity);
            }
        }
    }
}

void AIController::RotateEnemy()
{

}


