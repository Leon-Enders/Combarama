#pragma once
#include "Character.h"
#include "../Utility/ColorHelper.h"


class Enemy : public Character
{
public:
	Enemy(World* GameWorld);
	Enemy(World* GameWorld, const Transform& InTransform);
	virtual ~Enemy() = default;


	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;


	void UpdateVelocity(const Vector2& NewVelocity);

protected:

};