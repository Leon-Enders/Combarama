#pragma once
#include <functional>
#include <memory>
#include "GameObject.h"
#include "../Math/Transform.h"
#include "../Event/Delegate.h"


class Collider;
class World;


class Actor : public GameObject
{

public:
	Actor(World* GameWorld,const Transform& InTransform);
	virtual ~Actor() = default;

	inline const Vector2& GetPosition()const { return EntityTransform.Position; }
	inline const float& GetRotation()const { return EntityTransform.Rotation; }
	inline const Vector2& GetScale()const { return EntityTransform.Scale; }
	inline const Transform& GetTransform()const { return EntityTransform; }
	inline const Vector2 GetForwardVector()const {	return { cos(EntityTransform.Rotation), sin(EntityTransform.Rotation) };}


	void SetTransform(const Transform& NewTransform) { EntityTransform = NewTransform; }
	void SetPosition(const Vector2& NewPosition) { EntityTransform.Position = NewPosition; }
	void SetRotation(float NewRotation) { EntityTransform.Rotation = NewRotation; }
	void SetScale(const Vector2& NewScale) { EntityTransform.Scale = NewScale; }
	void SetInstigator(std::shared_ptr<Actor> InInstigator) { Instigator = InInstigator; }

protected:
	virtual void OnOverlapBegin(std::weak_ptr<Collider> OtherCollider);

	inline std::weak_ptr<Actor> GetInstigator()const { return Instigator; }

	//TODO: Move EntityTransform to private and fix compiler errors
	Transform EntityTransform;


private:
	
	//TODO: Actors should not have a instigator
	std::weak_ptr<Actor> Instigator;
	World* OwningWorld = nullptr;
	
};