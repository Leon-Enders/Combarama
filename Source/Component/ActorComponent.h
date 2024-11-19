#pragma once



class Actor;


class ActorComponent
{
public:
	virtual ~ActorComponent() = default;

	virtual void Initialize(Actor* InOwner);
	virtual void Update(float DeltaTime);
	virtual void FixedUpdate(float FixedDeltaTime);
	virtual void LateUpdate(float DeltaTime);

private:
	Actor* Owner;
};