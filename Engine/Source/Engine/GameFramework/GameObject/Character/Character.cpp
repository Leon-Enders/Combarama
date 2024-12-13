#include "Character.h"
#include "SDL3/SDL_log.h"
#include "../../../../RenderCore/Misc/ColorHelper.h"
#include "../../../../RenderCore/Misc/Avatar.h"
#include "../../../../Core/Coroutine/WaitSeconds.h"
#include "../../Component/PrimitiveComponent.h"

Character::Character(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld,InTransform)
{
	std::vector<SDL_Vertex> AvatarTriangles;
	Avatar::GenerateVertices(AvatarTriangles, GetTransform());

	CharacterPrimitive = CreateComponent<PrimitiveComponent>(std::move(AvatarTriangles));
}

void Character::Initialize()
{
	float ColliderWidth = Avatar::GetRadius() * 2.f;
	float ColliderHeight = Avatar::GetRadius() * 2.f;

	CharacterCollider = std::make_shared<Collider>(shared_from_this(), ColliderWidth, ColliderHeight);
	CharacterCollider->Initialize();
	CharacterCollider->OnOverlapBeginDelegate.BindMemberFunction<Character>(shared_from_this(), &Character::OnOverlapBegin);
}


void Character::SetController(std::shared_ptr<Controller> InOwningContoller)
{
	OwningController = InOwningContoller;
}

void Character::SetColor(const SDL_FColor& HeadColor, const SDL_FColor& BodyColor)
{
	Avatar::SetColor(HeadColor, BodyColor, CharacterPrimitive);
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

void Character::UpdatePosition(float DeltaTime)
{
	Vector2 NewPosition = Velocity * DeltaTime + GetPosition();
	SetPosition(NewPosition);
}

void Character::UpdateRotation()
{

}

void Character::OnOverlapBegin(std::weak_ptr<Collider> Other)
{
	CharacterCollider->OnOverlapBeginDelegate.Clear();
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

	UpdatePosition(FixedDeltaTime);
	UpdateRotation();
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