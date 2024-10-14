#pragma once
#include <unordered_map>
#include <memory>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "InputAction.h"
#include <vector>
#include <utility>



struct KeycodePackage
{
	KeycodePackage() = default;

	bool operator==(const KeycodePackage& other) const
	{
		
		return KeysToAxisMap == other.KeysToAxisMap;
	}

	void AddKeycode(SDL_Keycode KeyToAdd, E_AxisMapping AxisMapping)
	{
		KeysToAxisMap.insert({KeyToAdd,AxisMapping });
	}

	std::unordered_map<SDL_Keycode, E_AxisMapping> KeysToAxisMap;
};

template<>
struct std::hash<KeycodePackage>
{
	std::size_t operator()(const KeycodePackage& k) const
	{
		std::size_t seed = 0;
		for (const auto& pair : k.KeysToAxisMap)
		{
			std::size_t keyHash = std::hash<SDL_Keycode>()(pair.first);
			std::size_t valueHash = std::hash<int>()(static_cast<int>(pair.second));
			seed ^= keyHash ^ valueHash;
		}
		return seed;
	}
};


//Helper struct binding keycodes to an Input Action
//struct InputActionBinding
//{
//	InputActionBinding() = default;
//
//	void AddInputAction(const std::shared_ptr<InputAction>& InInputAction)
//	{
//		Action = InInputAction;
//	}
//
//	void AddKeyBind(SDL_Keycode KeyToBind, E_AxisMapping AxisMapping)
//	{
//		BoundKeys.push_back(KeyToBind);
//		KeysToAxisMap.insert({ KeyToBind,AxisMapping });
//	}
//
//	std::shared_ptr<InputAction> Action;
//	std::vector<SDL_Keycode> BoundKeys;
//
//	std::unordered_map<SDL_Keycode, E_AxisMapping> KeysToAxisMap;
//	
//};



class InputActionContext
{
public:
	InputActionContext()
	{

	}

	//TODO: InputAction should get added by SDL_Event, Key is too specific
	//TODO: Keycode is also too specific need something
	// like a wrapper which can take multiple keys,
	// then I can switch on keys and set InputActionValue
	// for each Key case for a single Action
	void AddInputActionBinding(KeycodePackage KeycodePackageToAdd, const std::shared_ptr<InputAction>& InputActionToAdd)
	{
		KeycodePackageToInputActions.insert({ KeycodePackageToAdd , InputActionToAdd });


		// populate keycode for KeycodePackageMap
		for (const auto& KeycodeAxisPair : KeycodePackageToAdd.KeysToAxisMap)
		{
			KeycodeToPackage.insert({ KeycodeAxisPair.first,KeycodePackageToAdd });
		}
	}

	//TODO a KeycodePackage should get passed here then I can iterate through all Keycodes of the keycode package and updatevalue on the input action and then execute it once
	void HandleKeyExecution(SDL_Keycode Keycode)
	{
		KeycodePackage CurrentKeycodePackage = KeycodeToPackage[Keycode];
		E_AxisMapping CurrentAxis = CurrentKeycodePackage.KeysToAxisMap[Keycode];

		InputAction* CurrentInputAction = KeycodePackageToInputActions[CurrentKeycodePackage].get();
		CurrentInputAction->GetActionValue().UpdateValue(CurrentAxis);
		CurrentInputAction->Execute();
	}
	void HandleKeyRelease(SDL_Keycode Keycode)
	{
		KeycodePackage CurrentKeycodePackage = KeycodeToPackage[Keycode];
		E_AxisMapping CurrentAxis = CurrentKeycodePackage.KeysToAxisMap[Keycode];

		InputAction* CurrentInputAction = KeycodePackageToInputActions[CurrentKeycodePackage].get();
		CurrentInputAction->GetActionValue().ClearValue(CurrentAxis);
		CurrentInputAction->Execute();
	}

	const bool HasKeycode(const SDL_Keycode& KeyToCheck)const
	{
		for (const auto& KeyCode : BoundKeys)
		{
			if (KeyToCheck == KeyCode)
			{
				return true;
			}
		}
		return false;
	}

private:
	std::vector<SDL_Keycode> BoundKeys;
	std::unordered_map<KeycodePackage,std::shared_ptr<InputAction>> KeycodePackageToInputActions;
	std::unordered_map<SDL_Keycode, KeycodePackage> KeycodeToPackage;
};