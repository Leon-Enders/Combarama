#pragma once
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include <unordered_map>
#include <memory>
#include <functional>


class InputAction
{
public:
	InputAction(const std::function<void()>& ActionDelegate)
		:
		InputActionDelegate(ActionDelegate)
	{
	
	}

	void Execute()
	{
		if (InputActionDelegate)
		{
			InputActionDelegate();
		}
	}

private:
	std::function<void()> InputActionDelegate;
};

class InputActionContext
{
public:
	InputActionContext(){}

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



class InputComponent
{
public:
	InputComponent()
	{
		Action = std::make_shared<InputAction>(std::bind(&InputComponent::TestPrint, this));

		ActionContext = std::make_unique<InputActionContext>();
		

		//Test Actions
		ActionContext->AddInputAction(SDLK_SPACE, Action);
	}

	void AddInputEvent(const SDL_Event& InputEvent)
	{
		ProcessedInputEvents.push_back(InputEvent);
	}

	void HandleInput()
	{
		// Go through all processed Inputs and Try to Execute Input Actions which may bound to them
		for (const auto& InputEvent : ProcessedInputEvents)
		{
			SDL_Keycode CurrentKey = InputEvent.key.key;

			if (ActionContext->HasKeycode(CurrentKey))
			{
				if (InputAction* CurrentInputAction = ActionContext->GetInputAction(CurrentKey))
				{
					CurrentInputAction->Execute();
				}
			}
			
		}

		// Clear all Inputs
		ProcessedInputEvents.clear();
	}


	void TestPrint()
	{
		SDL_Log("ActionExecuted");
	}

private:
	std::vector<SDL_Event> ProcessedInputEvents;

	std::shared_ptr<InputAction> Action = nullptr;
	std::unique_ptr<InputActionContext> ActionContext = nullptr;
};
