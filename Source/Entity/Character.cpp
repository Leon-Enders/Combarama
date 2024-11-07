#include "Character.h"
#include "../Render/Avatar.h"
#include "SDL3/SDL_log.h"
#include "../Utility/ColorHelper.h"

Character::Character(World* GameWorld)
	:
	Actor(GameWorld)
{
}

Character::Character(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld,InTransform)
{

	//Use helper function to generate Avatar Triangles
	std::vector<SDL_Vertex> AvatarTriangles;
	Avatar::GenerateVertices(AvatarTriangles, EntityTransform);

	//Move Avatar Triangles into Render Component
	CharacterRenderComponent = std::make_unique<RenderComponent>(*this, std::move(AvatarTriangles));

	float ColliderWidth = Avatar::GetRadius() * 2.f;
	float ColliderHeight = Avatar::GetRadius() * 2.f;

	CharacterCollider = std::make_shared<Collider>(this,ColliderWidth, ColliderHeight);
	CharacterCollider->Initialize();
	
}

void Character::Initialize()
{
	CharacterCollider->OnCollisionEntererDelegate.BindMemberFunction<Character>(shared_from_this(), &Character::OnCollisionEnter);
}

void Character::OnPossessed(Controller* OwningContoller)
{
	OwningController = OwningContoller;
}

void Character::SetColor(const SDL_FColor& HeadColor, const SDL_FColor& BodyColor)
{
	ColorResetCounter = 0;
	Avatar::SetColor(HeadColor, BodyColor, CharacterRenderComponent.get());
}

void Character::TakeDamage(int Damage)
{
	SetColor(COLOR_RED, COLOR_RED);

	Health -= Damage;
	if (Health <= 0)
	{
		OnDeathSignature.Broadcast();
		OnDeathSignature.Broadcast();
		Destroy();
	}
}

void Character::UpdatePosition(float DeltaTime)
{
	EntityTransform.Position += Velocity * DeltaTime;
}

void Character::UpdateRotation()
{

}

void Character::OnCollisionEnter(std::weak_ptr<Collider> Other)
{
	SDL_Log("COLLISION ENTER!");
	CharacterCollider->OnCollisionEntererDelegate.Clear();
}

void Character::OnCollisionExit(const Collider& Other)
{
	SDL_Log("Collision Exit");
}

void Character::HandleHitEffect()
{
	// Hit Effect
	ColorResetCounter++;
	if (ColorResetCounter >= ColorMaxTime)
	{
		SetColor(BodyColor, HeadColor);
	}
}

void Character::Update(float DeltaTime)
{
	HandleHitEffect();
}

void Character::FixedUpdate(float FixedDeltaTime)
{
	Actor::FixedUpdate(FixedDeltaTime);

	UpdatePosition(FixedDeltaTime);
	UpdateRotation();
}
