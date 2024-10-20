#pragma once
#include "../Math/Transform.h"


//TODO: Actor should not have an avatar per se, because avatar is a base shape for a character, I can create another primitive shape as a base for actor or even none
class Actor
{

public:
	Actor(const Transform& InTransform);
	virtual void Initialize();
	virtual void Update(float DeltaTime);

	const Vector2 GetPosition()const { return EntityTransform.Position; }
	const float GetRotation()const { return EntityTransform.Rotation; }
	const Vector2 GetScale()const { return EntityTransform.Scale; }

	void SetPosition(const Vector2& NewPosition) { EntityTransform.Position = NewPosition; }
	void SetRotation(float NewRotation) { EntityTransform.Rotation = NewRotation; }
	void SetScale(const Vector2& NewScale) { EntityTransform.Scale = NewScale; }
protected:

	Transform EntityTransform;
};