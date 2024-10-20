#pragma once
#include "Actor.h"
#include "../Render/RenderComponent.h"
#include <memory>

class Weapon : public Actor
{
public:
	Weapon(const Transform& InTransform);

	RenderComponent* GetRenderComponent() { return SwordRenderComponent.get(); }
private:

	Vector2 WeaponOffset = { 0.f, 100.f };

	std::unique_ptr<RenderComponent> SwordRenderComponent = nullptr;
};