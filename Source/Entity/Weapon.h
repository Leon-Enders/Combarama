#pragma once
#include "Actor.h"
#include "../Render/RenderComponent.h"
#include <memory>

class Weapon : public Actor
{
public:
	Weapon(World* GameWorld);
	Weapon(World* GameWorld, const Transform& InTransform);
	virtual ~Weapon() = default;

	RenderComponent* GetRenderComponent() { return SwordRenderComponent.get(); }
private:

	Transform LocalTransform = { {75.f,0.f},1.5708f,{1.f,1.f} };
	std::unique_ptr<RenderComponent> SwordRenderComponent = nullptr;
	
};