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


class InputActionContext
{
public:
	InputActionContext()
	{

	}
	void AddInputActionBinding(KeycodePackage KeycodePackageToAdd, const std::shared_ptr<InputAction>& InputActionToAdd)
	{
		KeycodePackageToInputActions.insert({ KeycodePackageToAdd , InputActionToAdd });


		// populate keycode for KeycodePackageMap
		for (const auto& KeycodeAxisPair : KeycodePackageToAdd.KeysToAxisMap)
		{
			BoundKeys.push_back(KeycodeAxisPair.first);
			KeycodeToPackage.insert({ KeycodeAxisPair.first,KeycodePackageToAdd });
		}
	}

	void AddLookInputAction(const std::shared_ptr<InputAction>& InputActionToAdd)
	{
		MouseInputAction = InputActionToAdd;
	}

	void AddQuitInputAction(const std::shared_ptr<InputAction>& InputActionToAdd)
	{
		QuitInputAction = InputActionToAdd;
	}

	void AddAttackInputAction(const std::shared_ptr<InputAction>& InputActionToAdd)
	{
		AttackInputAction = InputActionToAdd;
	}

	void HandleQuitEvent(const SDL_Event& QuitEvent)
	{
		if (QuitInputAction)
		{
			QuitInputAction->Execute();
		}
	}

	void HandleAttackEvent()
	{
		if (AttackInputAction)
		{
			AttackInputAction->Execute();
		}
	}

	void HandleMouseEvent(const SDL_Event& MouseEvent)
	{
		MouseInput.X = MouseEvent.motion.x;
		MouseInput.Y = MouseEvent.motion.y;

		if (MouseInputAction)
		{
			MouseInputAction->SetActionValue(MouseInput);
			MouseInputAction->Execute();
		}
	}


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
	std::shared_ptr<InputAction> MouseInputAction;
	std::shared_ptr<InputAction> QuitInputAction;
	std::shared_ptr<InputAction> AttackInputAction;
	Vector2 MouseInput;
};