#pragma once
#include "Character.h"
#include "ColorHelper.h"


class Enemy : public Character
{
public:
	Enemy(const Vector2& InPosition);

protected:
	virtual void Initialize() override;

private:

};