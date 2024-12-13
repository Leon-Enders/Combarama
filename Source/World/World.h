#pragma once
#include <vector>
#include <memory>
#include <ranges>
#include <unordered_map>
#include <typeindex>
#include <variant>
#include <functional>
#include "../Entity/GameObject.h"
#include "../Math/Transform.h"
#include "../System/WorldSubsystem/WorldSubsystem.h"

struct SDL_FColor;
class Controller;
class AIController;
class PlayerController;
class Actor;
class Weapon;
class Obstacle;
class Projectile;
class Character;
class Enemy;
class PlayerCharacter;



template<typename T>
concept IsGameObject = std::is_base_of<GameObject, T>::value;

template<typename T>
concept IsActor = std::is_base_of<Actor, T>::value;

template<typename T>
concept IsSubsystem = std::is_base_of<WorldSubsystem, T>::value;


using GameObjectVariant = std::variant<
	std::vector<std::weak_ptr<GameObject>>,
	std::vector<std::weak_ptr<Controller>>,
	std::vector<std::weak_ptr<AIController>>,
	std::vector<std::weak_ptr<PlayerController>>,
	std::vector<std::weak_ptr<Actor>>,
	std::vector<std::weak_ptr<Character>>,
	std::vector<std::weak_ptr<Enemy>>,
	std::vector<std::weak_ptr<PlayerCharacter>>,
	std::vector<std::weak_ptr<Weapon>>,
	std::vector<std::weak_ptr<Obstacle>>,
	std::vector<std::weak_ptr<Projectile>>>;

class Game;

class World
{
public:
	World(Game* theGame);
	void Initialize();
	
	void FixedUpdate(float FixedDeltaTime);
	void Update(float DeltaTime);
	void LateUpdate(float DeltaTime);
	void DrawDebug();


	template<IsGameObject T>
	std::weak_ptr<T> SpawnGameObject();

	template<IsActor T, typename... Args>
	std::weak_ptr<T> SpawnActor(const Transform& SpawnTransform, Args&& ... args);

	template<IsGameObject T>
	std::vector<std::shared_ptr<T>> GetAllGameObjectsOfClass();

	template<IsSubsystem T>
	T* GetSubsystem();


	void UpdateInstancedGameObjects();
	void CleanUpInstanceGameObjects();
	void RemoveGameObject(GameObject* GameObjectToRemove);


	Game* GetGame() { return theGame; }

private:
	template<IsGameObject T>
	void AddGameObjectToMap(std::shared_ptr<T> GameObjectToAdd);

	void FillSubsystemCollection();


private:

	std::unordered_map<std::type_index, GameObjectVariant> GameObjectTypeToGameObjectsMap;
	std::vector<std::unique_ptr<WorldSubsystem>> SubsystemCollection;
	std::vector<std::shared_ptr<GameObject>> InstancedGameObjects;

	std::vector<GameObject*> GameObjectsToRemove;
	std::vector<std::shared_ptr<GameObject>> GameObjectsToAdd;

	Game* theGame;
};

template<IsGameObject T>
inline std::weak_ptr<T> World::SpawnGameObject()
{
	std::shared_ptr<T> NewGameObject = std::make_shared<T>(this);
	std::weak_ptr<T> NewGameObjectWeak = NewGameObject;

	//Small hack to initialize GameObject
	GameObject* InitializationPtr = static_cast<GameObject*>(NewGameObject.get());
	InitializationPtr->Initialize();


	AddGameObjectToMap(NewGameObject);
	GameObjectsToAdd.push_back(std::move(NewGameObject));

	return NewGameObjectWeak;
}

template<IsActor T, typename... Args>
inline std::weak_ptr<T> World::SpawnActor(const Transform& SpawnTransform, Args&& ... args)
{
	std::shared_ptr<T> NewGameObject = std::make_shared<T>(this, SpawnTransform, std::forward<Args>(args)...);
	std::weak_ptr<T> NewGameObjectWeak = NewGameObject;

	//Small hack to initialize GameObject
	GameObject* InitializationPtr = static_cast<GameObject*>(NewGameObject.get());
	InitializationPtr->Initialize();
	
	
	AddGameObjectToMap(NewGameObject);
	GameObjectsToAdd.push_back(std::move(NewGameObject));
	
	return NewGameObjectWeak;
}

template <IsGameObject T>
std::vector<std::shared_ptr<T>> World::GetAllGameObjectsOfClass()
{
	std::type_index TypeIndex = std::type_index(typeid(T));
	auto it = GameObjectTypeToGameObjectsMap.find(TypeIndex);

	if (it != GameObjectTypeToGameObjectsMap.end()) {
		auto& WeakGameObjectVector = std::get<std::vector<std::weak_ptr<T>>>(it->second);

		std::vector<std::shared_ptr<T>> ValidGameObjects;
		WeakGameObjectVector.erase(std::remove_if(WeakGameObjectVector.begin(), WeakGameObjectVector.end(),
			[&ValidGameObjects](const std::weak_ptr<T>& WeakPtr)
			{
				if (auto SharedPtr = WeakPtr.lock())
				{
					ValidGameObjects.push_back(SharedPtr);
					return false;
				}
				return true; 
			}), WeakGameObjectVector.end());

		return ValidGameObjects;
	}

	return {};
}

template<IsGameObject T>
inline void World::AddGameObjectToMap(std::shared_ptr<T> GameObjectToAdd)
{
	std::type_index TypeIndex = std::type_index(typeid(T));

	auto it = GameObjectTypeToGameObjectsMap.find(TypeIndex);
	if (it == GameObjectTypeToGameObjectsMap.end()) 
	{
		std::vector<std::weak_ptr<T>> NewVector;
		GameObjectTypeToGameObjectsMap[TypeIndex] = NewVector;
		it = GameObjectTypeToGameObjectsMap.find(TypeIndex);
	}

	auto& GameObjectVector = std::get<std::vector<std::weak_ptr<T>>>(it->second);
	GameObjectVector.push_back(GameObjectToAdd);
}


template<IsSubsystem T>
inline T* World::GetSubsystem()
{
	auto Iterator = std::ranges::find_if(SubsystemCollection,
		[](const std::unique_ptr<WorldSubsystem>& Subsystem)
		{
			return dynamic_cast<T*>(Subsystem.get()) != nullptr;
		});

	if (Iterator != SubsystemCollection.end()) 
	{
		return dynamic_cast<T*>(Iterator->get());
	}

	return nullptr;
}




