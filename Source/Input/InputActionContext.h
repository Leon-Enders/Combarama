#pragma once
#include <unordered_map>
#include <memory>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "InputAction.h"
#include <vector>
#include <utility>



//Helper struct binding values for a certain keycode
struct InputValueMappingContext
{



	
};



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
	void AddInputAction(const std::shared_ptr<InputAction>& InputActionToAdd)
	{
		for (auto& pair : KeyToAxisMap)
		{
			KeyToInputActionMap.insert(std::make_pair(pair.first, InputActionToAdd));
			BoundKeys.push_back(pair.first);
		}
		
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

	std::unordered_map<SDL_Keycode, E_AxisMapping> KeyToAxisMap
	{
		{SDLK_W, E_AxisMapping::Up},
		{SDLK_S, E_AxisMapping::Down},
		{SDLK_D, E_AxisMapping::Right},
		{SDLK_A, E_AxisMapping::Left}
	};
private:
	std::vector<SDL_Keycode> BoundKeys;
	std::unordered_map<SDL_Keycode, std::shared_ptr<InputAction>> KeyToInputActionMap;

	
};