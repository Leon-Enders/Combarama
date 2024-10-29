#pragma once



struct Vector2;
class Character;
class World;


class Controller
{
public:
	
	Controller(World* InOwningWorld);

	virtual void PossessCharacter(Character* CharacterToPossess);
	virtual void UnPossessCharacter();
	

protected:
	virtual void Initialize();
	World* GetWorld()const{ return OwningWorld; }

	Character* ControlledCharacter = nullptr;

private:
	World* OwningWorld;
	
};