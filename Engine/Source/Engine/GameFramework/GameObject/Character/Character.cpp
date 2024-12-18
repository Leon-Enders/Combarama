#include "Character.h"
#include "SDL3/SDL_log.h"
#include "../../../../RenderCore/Misc/ColorHelper.h"
#include "../../../../RenderCore/Misc/PrimitiveFactory.h"
#include "../../../../Core/Coroutine/WaitSeconds.h"
#include "../../Component/PrimitiveComponent.h"
#include "../../Component/MovementComponent.h"

Character::Character(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld,InTransform)
{
	CharacterPrimitive = CreateComponent<PrimitiveComponent>(std::move(AvatarPrimitive::Make()));
	CharacterPrimitive->SetCollisionShape(CollisionShape::MakeCircle(25.f));
	CharacterPrimitive->AttachToComponent(GetRootComponent());
	CharacterMovementComponent = CreateComponent<MovementComponent>();
}

void Character::Initialize()
{
	float ColliderWidth = 20 * 2.f;
	float ColliderHeight = 20 * 2.f;
}


void Character::SetController(std::shared_ptr<Controller> InOwningContoller)
{
	OwningController = InOwningContoller;
}

void Character::SetColor(const SDL_FColor& HeadColor, const SDL_FColor& BodyColor)
{
	//TODO: Need way to Colour Body Parts differently, I dont want more than 1 primitive Component for the character..
	CharacterPrimitive->SetColor(HeadColor);
}

void Character::TakeDamage(int Damage)
{
	
	ApplyHitEffect(0.15f);
	Health -= Damage;
	if (Health <= 0)
	{
		OnCharacterDeath();
		Destroy();
	}
}

void Character::OnOverlapBegin(std::weak_ptr<Collider> Other)
{
}

void Character::OnCharacterDeath()
{

}

Controller* Character::GetController()
{
	if (auto sControllerptr = OwningController.lock())
	{
		return sControllerptr.get();
	}

	return nullptr;
}

PrimitiveComponent* Character::GetCharacterPrimitive() const
{
	return CharacterPrimitive;
}


void Character::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
}

void Character::FixedUpdate(float FixedDeltaTime)
{
	Actor::FixedUpdate(FixedDeltaTime);
}

void Character::AddMoveInput(const Vector2& MoveInput)
{
	PendingInputVector += MoveInput.GetNormalized();
}

Vector2 Character::ConsumeInputVector()
{
	Vector2 CachedInputVector = PendingInputVector;
	PendingInputVector = Vector2::Zero();
	return CachedInputVector;
}

Coroutine Character::ApplyHitEffect(float Duration)
{
	if (IsHit) co_return;
	IsHit = true;
	SetColor(COLOR_RED, COLOR_RED);
	co_await WaitSeconds(Duration, this);
	SetColor(BodyColor, HeadColor);
	IsHit = false;
}