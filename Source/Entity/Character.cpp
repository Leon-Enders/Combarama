#include "Character.h"
#include "../Render/Avatar.h"

Character::Character(const Transform& InTransform)
	:
	Actor(InTransform)
{
	//Use helper function to generate Avatar Triangles
	std::vector<SDL_Vertex> AvatarTriangles;
	Avatar::GenerateVertices(AvatarTriangles, EntityTransform);

	//Move Avatar Triangles into Render Component
	CharacterRenderComponent = std::make_unique<RenderComponent>(std::move(AvatarTriangles),EntityTransform);
}

void Character::OnPossessed(Controller* OwningContoller)
{
	OwningController = OwningContoller;
}

void Character::UpdatePosition(float DeltaTime)
{
	EntityTransform.Position += Velocity * DeltaTime * Speed;
	CharacterRenderComponent->UpdatePosition(EntityTransform.Position);
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
