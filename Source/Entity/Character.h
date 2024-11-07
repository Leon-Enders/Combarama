#pragma once
#include <memory>
#include "Actor.h"
#include "../Controller/Controller.h"
#include "../Render/RenderComponent.h"
#include "../Collision/Collider.h"
#include "../Event/Delegate.h"



//TODO: Create overload for OwningController for PlayerController
class Character : public Actor , public std::enable_shared_from_this<Character>
{
public:
	Character(World* GameWorld, const Transform& InTransform);
	virtual ~Character() = default;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float FixedDeltaTime) override;

	void OnPossessed(Controller* OwningContoller);
	const Vector2& GetVelocity()const { return Velocity; }

	void SetColor(const SDL_FColor& HeadColor, const SDL_FColor& BodyColor);


	//TODO: CombatInterface or Component
	void TakeDamage(int Damage);


	MulticastDelegate<void, void> OnDeathSignature;

protected:
	virtual void UpdatePosition(float DeltaTime);
	virtual void UpdateRotation();

	
	virtual void OnOverlapBegin(std::weak_ptr<Collider> OtherCollider) override;

protected:
	float Speed = 250.f;
	Vector2 Velocity = { 0.f, 0.f };
	
	//TODO: Change to Weak Ptr
	Controller* OwningController = nullptr;
	std::unique_ptr<RenderComponent> CharacterRenderComponent = nullptr;
	std::shared_ptr<Collider> CharacterCollider = nullptr;


	int ColorResetCounter = 0;
	int ColorMaxTime = 15;

	int Health = 20;


	SDL_FColor HeadColor;
	SDL_FColor BodyColor;
private:

	void HandleHitEffect();
};