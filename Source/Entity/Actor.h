#pragma once
#include <functional>
#include <memory>
#include "GameObject.h"
#include "../Math/Transform.h"
#include "../Event/Delegate.h"
#include "../Component/ActorComponent.h"

class Collider;
class World;

template<typename T>
concept IsActorComponent = std::is_base_of<ActorComponent, T>::value;



class Actor : public GameObject
{

public:
	Actor(World* GameWorld,const Transform& InTransform);
	virtual ~Actor() = default;


	virtual void Initialize();
	virtual void Update(float DeltaTime);
	virtual void FixedUpdate(float FixedDeltaTime);
	virtual void LateUpdate(float DeltaTime);


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

	template<IsActorComponent T>
	std::weak_ptr<T> CreateComponent();
private:
	
	//TODO: Actors should not have a instigator
	std::weak_ptr<Actor> Instigator;
	World* OwningWorld = nullptr;
	

	//Actor Components
	std::vector<std::shared_ptr<ActorComponent>> ActorComponents;
};

template<IsActorComponent T>
inline std::weak_ptr<T> Actor::CreateComponent()
{
	auto sComponentPtr = std::make_shared<ActorComponent>();
	std::weak_ptr<T> wComponentPtr = sComponentPtr;

	ActorComponent* InitializationPtr = static_cast<ActorComponent*>(sComponentPtr.get());
	InitializationPtr->Initialize();

	ActorComponents.push_back(std::move(sComponentPtr));

	return wComponentPtr;
}
