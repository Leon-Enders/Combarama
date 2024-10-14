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
		InputSystem::Get().AddInputComponent(this);
	}

	~InputComponent()
	{
		InputSystem::Get().RemoveInputComponent(this);
	}

	void SetInputActionContext(InputActionContext* InActionContext)
	{
		ActionContext = InActionContext;
	}

	//TODO: Before pushing input event filter if it is in the Action Context
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
					switch (CurrentInputAction->GetActionValue())
					{
					case ActionValueType::None:
						CurrentInputAction->Execute();
						break;
					case ActionValueType::Vector:
						CurrentInputAction->Execute(UpVector);
					default:
						break;
					}
				}
			}
			
		}

		// Clear all Inputs
		ProcessedInputEvents.clear();
	}

private:
	Vector2 UpVector = Vector2(-1.f, 0.f);

	std::vector<SDL_Event> ProcessedInputEvents;

	InputActionContext* ActionContext = nullptr;
};
