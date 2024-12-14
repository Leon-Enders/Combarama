#pragma once
#include <functional>
#include <memory>
#include "GameObject.h"
#include "../../../Core/Math/Transform.h"
#include "../../../Core/Event/Delegate.h"
#include "../Component/ActorComponent.h"

class PrimitiveComponent;
class SceneComponent;
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


	const Transform& GetTransform()const;
	const Vector2& GetPosition()const;
	const float GetRotation()const;
	const Vector2& GetScale()const;
	const Vector2 GetForwardVector()const;

	void SetTransform(const Transform& InTransform);
	void SetPosition(const Vector2& InPosition);
	void SetRotation(float InRotation);
	void SetScale(const Vector2& InScale);
	void SetInstigator(std::shared_ptr<Actor> InInstigator) { Instigator = InInstigator; }

protected:
	virtual void OnOverlapBegin(std::weak_ptr<Collider> OtherCollider);

	inline std::weak_ptr<Actor> GetInstigator()const { return Instigator; }


	template<IsActorComponent T, typename... Args>
	T* CreateComponent(Args&&... args);

	const SceneComponent* GetRootComponent()const { return RootComponent; }
private:
	
	//TODO: Actors should not have a instigator
	std::weak_ptr<Actor> Instigator;
	World* OwningWorld = nullptr;
	

	//Actor Components
	std::vector<std::unique_ptr<ActorComponent>> ActorComponents;

	SceneComponent* RootComponent;
};

template<IsActorComponent T, typename... Args>
inline T* Actor::CreateComponent(Args&&... args)
{
	auto sComponentPtr = std::make_unique<T>(this, std::forward<Args>(args)...);
	T* ComponentPtr = sComponentPtr.get();

	ActorComponent* InitializationPtr = static_cast<ActorComponent*>(ComponentPtr);
	InitializationPtr->Initialize();

	ActorComponents.push_back(std::move(sComponentPtr));

	return ComponentPtr;
}
