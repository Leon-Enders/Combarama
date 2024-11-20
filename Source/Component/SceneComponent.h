#pragma once
#include "ActorComponent.h"
#include "../Math/Matrix.h"
#include "../Event/Delegate.h"


class SceneComponent : public ActorComponent
{
public:
	virtual ~SceneComponent();
	virtual void Initialize(Actor* InOwner) override;
	virtual void Update(float DeltaTime) override;

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
	Matrix3x3 LocalTransformMatrix;

private:
	void UpdateLocalMatrix();
};