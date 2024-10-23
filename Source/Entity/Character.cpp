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
	//Use helper function to generate Avatar Triangles
	std::vector<SDL_Vertex> AvatarTriangles;
	Avatar::GenerateVertices(AvatarTriangles, EntityTransform);

	//Move Avatar Triangles into Render Component
	CharacterRenderComponent = std::make_unique<RenderComponent>(std::move(AvatarTriangles),*this);

	float ColliderWidth = Avatar::GetRadius() * 2.f;
	float ColliderHeight = Avatar::GetRadius() * 2.f;

	CharacterCollider = std::make_unique<Collider>(InTransform.Position, ColliderWidth, ColliderHeight);

}

void Character::OnPossessed(Controller* OwningContoller)
{
	OwningController = OwningContoller;
}

void Character::UpdatePosition(float DeltaTime)
{
	EntityTransform.Position += Velocity * DeltaTime * Speed;


	CharacterCollider->UpdatePosition(EntityTransform.Position);
}

void Character::UpdateRotation()
{
}

void Character::Initialize()
{

}

void Character::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	UpdatePosition(DeltaTime);
	UpdateRotation();
}
