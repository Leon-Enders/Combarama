#include "Character.h"
#include "../Render/Avatar.h"

Character::Character(World* GameWorld)
	:
	Actor(GameWorld)
{
}

Character::Character(World* GameWorld, const Transform& InTransform)
	:
	Actor(GameWorld,InTransform)
{
	using namespace std::placeholders;

	//Use helper function to generate Avatar Triangles
	std::vector<SDL_Vertex> AvatarTriangles;
	Avatar::GenerateVertices(AvatarTriangles, EntityTransform);

	//Move Avatar Triangles into Render Component
	CharacterRenderComponent = std::make_unique<RenderComponent>(*this, std::move(AvatarTriangles));

	float ColliderWidth = Avatar::GetRadius() * 2.f;
	float ColliderHeight = Avatar::GetRadius() * 2.f;

	CharacterCollider = std::make_unique<Collider>(this,ColliderWidth, ColliderHeight);
	CharacterCollider->OnCollisionEnterDelegate = std::bind(&Character::OnCollisionEnter, this,_1);
}

void Character::OnPossessed(Controller* OwningContoller)
{
	OwningController = OwningContoller;
}

void Character::UpdatePosition(float DeltaTime)
{
	EntityTransform.Position += Velocity * DeltaTime;
}

void Character::UpdateRotation()
{
}

void Character::OnCollisionEnter(const Collider& Other)
{
	
}

void Character::OnCollisionExit(const Collider& Other)
{
	SDL_Log("Collision Exit");
}

void Character::Initialize()
{

}

void Character::Update(float DeltaTime)
{

}

void Character::FixedUpdate(float FixedDeltaTime)
{
	Actor::FixedUpdate(FixedDeltaTime);

	UpdatePosition(FixedDeltaTime);
	UpdateRotation();
}
