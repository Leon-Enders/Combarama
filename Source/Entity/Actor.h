#pragma once
#include "../Math/Transform.h"


class Actor
{

public:
	Actor();
	Actor(const Transform& InTransform);
	~Actor();
	virtual void Initialize();
	virtual void Update(float DeltaTime);

	inline const Vector2 GetPosition()const { return EntityTransform.Position; }
	inline const float GetRotation()const { return EntityTransform.Rotation; }
	inline const Vector2 GetScale()const { return EntityTransform.Scale; }
	inline const Transform GetTransform()const { return EntityTransform; }

	void SetTransform(const Transform& NewTransform) { EntityTransform = NewTransform; }
	void SetPosition(const Vector2& NewPosition) { EntityTransform.Position = NewPosition; }
	void SetRotation(float NewRotation) { EntityTransform.Rotation = NewRotation; }
	void SetScale(const Vector2& NewScale) { EntityTransform.Scale = NewScale; }
protected:

	Transform EntityTransform;
};