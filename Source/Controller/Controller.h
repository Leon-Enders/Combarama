#pragma once
#include <memory>


struct Vector2;
class Character;
class World;


class Controller 
{
public:
	
	Controller(World* InOwningWorld);

	virtual void Update(float DeltaTime);


	virtual void PossessCharacter(std::shared_ptr<Character> CharacterToPossess);
	virtual void UnPossessCharacter();
	

protected:
	virtual void Initialize();
	World* GetWorld()const{ return OwningWorld; }

	std::weak_ptr<Character> ControlledCharacter;

private:
	World* OwningWorld;
	
};