#pragma once
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include <unordered_map>
#include <memory>
#include <functional>
#include "InputSystem.h"
#include "InputAction.h"
#include "InputActionContext.h"



class InputComponent
{
public:
	InputComponent()
	{
		Action = std::make_shared<InputAction>(std::bind(&InputComponent::TestPrint, this));

		ActionContext = std::make_unique<InputActionContext>();
		

		//Test Actions
		ActionContext->AddInputAction(SDLK_SPACE, Action);

		InputSystem::Get().AddInputComponent(this);
	}

	~InputComponent()
	{
		InputSystem::Get().RemoveInputComponent(this);
	}

	void ReceiveInputEvent(const SDL_Event& InputEvent)
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
