#pragma once
#include "PrimitiveComponent.h"



class WeaponComponent : public PrimitiveComponent
{
public:
	virtual void Initialize(Actor* Owner) override;

};