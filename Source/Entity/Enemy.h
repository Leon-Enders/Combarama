#pragma once
#include "Character.h"
#include "../Utility/ColorHelper.h"


class Enemy : public Character
{
public:
	Enemy(const Vector2& InPosition);
	virtual void Initialize() override;
};