#pragma once
#include <memory>
#include <variant>
#include "SDL3/SDL_pixels.h"
#include "../Actor.h"
#include "../../../Physics/Collider.h"
#include "../../../../Core/Event/Delegate.h"
#include "../../../../Core//Coroutine/Coroutine.h"
#include "../Controller/Controller.h"

class PrimitiveComponent;
class MovementComponent;

class Character : public Actor , public std::enable_shared_from_this<Character>
{
public:
	Character(World* GameWorld, const Transform& InTransform);
	virtual ~Character() = default;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float FixedDeltaTime) override;


	void AddMoveInput(const Vector2& MoveInput);
	
	Vector2 ConsumeInputVector();

	void SetController(std::shared_ptr<Controller> InOwningContoller);
	//TODO: CombatInterface or Component
	void TakeDamage(int Damage);

protected:
	virtual void OnOverlapBegin(std::weak_ptr<Collider> OtherCollider) override;
	virtual void OnCharacterDeath();


	Controller* GetController();
	PrimitiveComponent* GetCharacterPrimitive()const;
	void SetColor(const SDL_FColor& HeadColor, const SDL_FColor& BodyColor);

protected:
	Vector2 PendingInputVector;

	int Health = 20;

	SDL_FColor HeadColor = {1.f,1.f,1.f,1.f};
	SDL_FColor BodyColor = {1.f,1.f,1.f,1.f};
private:
	
	std::weak_ptr<Controller> OwningController;
	PrimitiveComponent* CharacterPrimitive = nullptr;
	MovementComponent* CharacterMovementComponent = nullptr;

	bool IsHit = false;
	Coroutine ApplyHitEffect(float Duration);
};