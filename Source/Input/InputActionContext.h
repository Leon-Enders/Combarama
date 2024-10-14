#pragma once
#include <unordered_map>
#include <memory>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "InputAction.h"


class InputActionContext
{
public:
	InputActionContext() {}

	//TODO: InputAction should get added by SDL_Event, Key is too specific
	void AddInputAction(SDL_Keycode KeyToBind, const std::shared_ptr<InputAction>& InputAction)
	{
		BoundKeys.push_back(KeyToBind);
		KeyToInputActionMap.insert(std::make_pair(KeyToBind, InputAction));
	}

	InputAction* GetInputAction(SDL_Keycode KeyPressed)
	{
		auto Iterator = KeyToInputActionMap.find(KeyPressed);
		if (Iterator != KeyToInputActionMap.end())
		{
			return Iterator->second.get();
		}
		SDL_Log("InputAction not found");
		return nullptr;
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
	std::unordered_map<SDL_Keycode, std::shared_ptr<InputAction>> KeyToInputActionMap;
};