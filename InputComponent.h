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

	void AddInputAction(SDL_Keycode KeyPressed, const std::shared_ptr<InputAction>& InputAction)
	{
		KeyToInputActionMap.insert(std::make_pair(KeyPressed, InputAction));
	}

	const InputAction* GetInputAction(SDL_Keycode KeyPressed)
	{
		auto Iterator = KeyToInputActionMap.find(KeyPressed);
		if (Iterator != KeyToInputActionMap.end())
		{
			return Iterator->second.get();
		}
		SDL_Log("InputAction not found");
	}

private:
	std::unordered_map<SDL_Keycode, std::shared_ptr<InputAction>> KeyToInputActionMap;
};



class InputComponent
{
public:
	InputComponent()
	{
		Action = std::make_shared<InputAction>(TestPrint);

		ActionContext = std::make_unique<InputActionContext>();
		ActionContext->AddInputAction(SDLK_SPACE, Action);
	}

	void AddInputEvent(const SDL_Event& InputEvent)
	{
		ProcessedInputEvents.push_back(InputEvent);
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
