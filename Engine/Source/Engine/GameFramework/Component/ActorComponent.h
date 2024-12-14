#pragma once
#include <memory>
#include <vector>
#include "../../../Core/Math/Transform.h"


class Actor;


class ActorComponent
{
public:
	ActorComponent(Actor* Owner);
	virtual ~ActorComponent();

	virtual void Initialize();
	virtual void Update(float DeltaTime);
	virtual void FixedUpdate(float FixedDeltaTime);
	virtual void LateUpdate(float DeltaTime);

	const Actor* GetOwner()const { return Owner; }
private:

	Actor* Owner = nullptr;
};