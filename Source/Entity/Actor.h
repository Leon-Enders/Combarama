#pragma once
#include <functional>
#include "../Math/Transform.h"

class World;

class Actor
{

public:
	Actor(World* GameWorld);
	Actor(World* GameWorld,const Transform& InTransform);
	virtual ~Actor() = default;

	virtual void Initialize();
	virtual void Update(float DeltaTime);
	virtual void FixedUpdate(float FixedDeltaTime);
	virtual void Destroy();



	virtual void DrawDebug();


	inline const Vector2& GetPosition()const { return EntityTransform.Position; }
	inline const float& GetRotation()const { return EntityTransform.Rotation; }
	inline const Vector2& GetScale()const { return EntityTransform.Scale; }
	inline const Transform& GetTransform()const { return EntityTransform; }

	inline const Vector2 GetForwardVector()const {	return { cos(EntityTransform.Rotation), sin(EntityTransform.Rotation) };}


	void SetTransform(const Transform& NewTransform) { EntityTransform = NewTransform; }
	void SetPosition(const Vector2& NewPosition) { EntityTransform.Position = NewPosition; }
	void SetRotation(float NewRotation) { EntityTransform.Rotation = NewRotation; }
	void SetScale(const Vector2& NewScale) { EntityTransform.Scale = NewScale; }


public:
	std::function<void(void)> OnDestroyDelegate;


protected:
	inline World* GetWorld()const { return OwningWorld; }

	Transform EntityTransform;

private:

	World* OwningWorld = nullptr;
};