#pragma once
#include "ActorComponent.h"



class SceneComponent : public ActorComponent
{
public:
	virtual ~SceneComponent();
	const Transform& GetTransform()const;
	const Vector2& GetPosition()const;
	const float GetRotation()const;
	const Vector2& GetScale()const;
	const Vector2 GetForwardVector()const;

	void SetTransform(const Transform& InTransform);
	void SetPosition(const Vector2& InPosition);
	void SetRotation(float InRotation);
	void SetScale(const Vector2& InScale);
	

protected:
	Transform ComponentTransform;
};