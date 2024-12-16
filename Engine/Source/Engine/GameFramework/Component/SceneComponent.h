#pragma once
#include "ActorComponent.h"
#include "../../../Core/Math/Matrix.h"
#include "../../../Core/Event/Delegate.h"


class SceneComponent : public ActorComponent
{
public:
	SceneComponent(Actor* Owner);
	virtual ~SceneComponent();

	virtual void Initialize() override;

	const Transform& GetTransform()const;
	const Vector2& GetPosition()const;
	const float GetRotation()const;
	const Vector2& GetScale()const;
	const Vector2 GetForwardVector()const;

	void SetTransform(const Transform& InTransform);
	void SetPosition(const Vector2& InPosition);
	void SetRotation(float InRotation);
	void SetScale(const Vector2& InScale);
	
	void AttachToComponent(const SceneComponent* Component);

	const TMatrix GetLocalMatrix()const;
	const TMatrix GetWorldMatrix()const;
	const Transform GetWorldTransform()const;
protected:
	Transform LocalTransform;
	
private:
	const SceneComponent* ParentComponent = nullptr;


	//TODO: Create SceneGraph setup
	std::vector<SceneComponent*> Children;
};