#pragma once
#include <memory>
#include <vector>
#include "../Math/Transform.h"


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


protected:
	Actor* GetOwner()const { return Owner; }
	const Transform& GetWorldTransform()const;

private:

	Actor* Owner = nullptr;
	ActorComponent* Parent = nullptr;
	std::vector<ActorComponent*> Children;
};