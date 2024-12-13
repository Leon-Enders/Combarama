#pragma once
#include <memory>
#include "../GameObject.h"


struct Vector2;
class Character;
class World;


class Controller : public GameObject
{
public:
	
	Controller(World* OwningWorld);
	~Controller()=default;

	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;

	virtual void PossessCharacter(std::shared_ptr<Character> CharacterToPossess);
	virtual void UnPossessCharacter();
	
	float GetControlRotation() { return ControlRotation; };

protected:

	float ControlRotation = 0.f;
	std::weak_ptr<Character> ControlledCharacter;
};