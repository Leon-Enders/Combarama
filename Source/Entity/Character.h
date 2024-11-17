#pragma once
#include <memory>
#include <variant>
#include "Actor.h"
#include "../Render/RenderComponent.h"
#include "../Collision/Collider.h"
#include "../Event/Delegate.h"
#include "../Coroutine/Coroutine.h"
#include "../Controller/Controller.h"



//TODO: Create overload for OwningController for PlayerController
class Character : public Actor , public std::enable_shared_from_this<Character>
{
public:
	Character(World* GameWorld, const Transform& InTransform);
	virtual ~Character() = default;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float FixedDeltaTime) override;


	const Vector2& GetVelocity()const { return Velocity; }


	void SetController(std::shared_ptr<Controller> InOwningContoller);

	//TODO: Move in protected?
	


	//TODO: CombatInterface or Component
	void TakeDamage(int Damage);

protected:
	virtual void UpdatePosition(float DeltaTime);
	virtual void UpdateRotation();

	virtual void OnOverlapBegin(std::weak_ptr<Collider> OtherCollider) override;
	virtual void OnCharacterDeath();


	Controller* GetController();
	void SetColor(const SDL_FColor& HeadColor, const SDL_FColor& BodyColor);

protected:
	float Speed = 250.f;
	Vector2 Velocity = { 0.f, 0.f };
	


	std::unique_ptr<RenderComponent> CharacterRenderComponent = nullptr;
	std::shared_ptr<Collider> CharacterCollider = nullptr;

	int Health = 20;

	SDL_FColor HeadColor;
	SDL_FColor BodyColor;
private:

	std::weak_ptr<Controller> OwningController;

	bool IsHit = false;
	Coroutine ApplyHitEffect(float Duration);
};