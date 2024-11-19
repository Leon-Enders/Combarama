#pragma once
#include <memory>
#include <vector>
#include "../Math/Transform.h"


class Actor;


class ActorComponent
{
public:
	virtual ~ActorComponent();

	virtual void Initialize(Actor* InOwner);
	virtual void Update(float DeltaTime);
	virtual void FixedUpdate(float FixedDeltaTime);
	virtual void LateUpdate(float DeltaTime);


protected:
	const Transform& GetWorldTransform()const;

private:

	Actor* Owner = nullptr;
	ActorComponent* Parent = nullptr;
	std::vector<ActorComponent*> Children;
};