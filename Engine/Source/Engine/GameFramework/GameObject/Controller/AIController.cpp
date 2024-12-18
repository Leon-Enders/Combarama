#include "AIController.h"
#include <ctime>
#include <chrono>
#include "../Character/Enemy.h"
#include "../Character/PlayerCharacter.h"
#include "../../../../Core/Math/ComboramaMath.h"
#include "../../World/World.h"
#include "../../../../Core/Misc/ComboramaRandom.h"

AIController::AIController(World* InOwningWorld)
    :
    Controller(InOwningWorld)
{
}

void AIController::Update(float DeltaTime)
{
    CheckForTarget();
    MoveEnemy();
    HandleAttack();
   
}

void AIController::PossessCharacter(std::shared_ptr<Character> CharacterToPossess)
{
    ControlledEnemy = std::dynamic_pointer_cast<Enemy>(CharacterToPossess);


    if (auto sEnemyPtr = ControlledEnemy.lock())
    {
        sEnemyPtr->SetController(shared_from_this());

        StartPosition = sEnemyPtr->GetPosition();
        sEnemyPtr->AddMoveInput({ 1.f,0.f });

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
     
        auto PlayerCharacters = GetWorld()->GetAllGameObjectsOfClass<PlayerCharacter>();

        for (const auto& PlayerChar : PlayerCharacters)
        {
            Vector2 DeltaPosition = PlayerChar->GetPosition() - sEnemyPtr->GetPosition();
            float Size = std::abs(DeltaPosition.Size());
            if (Size < PullRange)
            {
                IsPulled = true;
                Target = PlayerChar;
            }
        }
    }

   
}

void AIController::HandleAttack()
{
    if (Target.expired() || ControlledEnemy.expired()) return;

    if (CanAttack) Attack();
}



void AIController::UnPossessCharacter()
{
    ControlledEnemy.reset();

    //Temp solution: Remove from The world
    GetWorld()->RemoveGameObject(this);
}

void AIController::MoveEnemy()
{
    if (auto sEnemyPtr = ControlledEnemy.lock())
    {
        if (auto sTargetPtr = Target.lock())
        {
            Vector2 TargetDirection = sTargetPtr->GetPosition().DirectionToTarget(sEnemyPtr->GetPosition());
            sEnemyPtr->AddMoveInput(TargetDirection);
        }
        else
        {
            VelocityUpdateCounter++;
            if (VelocityUpdateCounter > VelocityMaxUpdateCounter)
            {
                VelocityUpdateCounter = 0;

                std::uniform_real_distribution<float> DistFloatWidth(-1.f, 1.f);
                std::uniform_real_distribution<float> DistFloatHeight(-1.f, 1.f);


                Vector2 MoveInput = { DistFloatWidth(RandomGenerator::GetRandomEngine()) , DistFloatHeight(RandomGenerator::GetRandomEngine()) };

                sEnemyPtr->AddMoveInput(MoveInput);
                ControlRotation = MoveInput.Normalize().LookAtRotation(sEnemyPtr->GetForwardVector());
            }
        }
    }
}

Coroutine AIController::Attack()
{
   CanAttack = false;
   Enemy* EnemyPtr = ControlledEnemy.lock().get();
   EnemyPtr->Attack();
   co_await WaitSeconds(AttackCooldown, this);
   CanAttack = true;

}


