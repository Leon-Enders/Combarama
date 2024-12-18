#pragma once
#include <memory>
#include <vector>
#include "../../../Core/Math/Transform.h"


class Actor;
class World;

class ActorComponent
{
public:
	ActorComponent(Actor* Owner);
	virtual ~ActorComponent();

	virtual void Initialize();
	virtual void Update(float DeltaTime);
	virtual void FixedUpdate(float FixedDeltaTime);
	virtual void LateUpdate(float DeltaTime);

	Actor* GetOwner()const { return Owner; }
	World* GetWorld()const;
private:

	Actor* Owner = nullptr;
};