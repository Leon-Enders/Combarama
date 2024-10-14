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
	void ReceiveInputEvent(const bool* InputEvent)
	{
		if (InputEvent[SDL_SCANCODE_W])
		{
			ProcessedInputEvents.push_back(SDLK_W);
		}
		else if(!InputEvent[SDL_SCANCODE_A] && !InputEvent[SDL_SCANCODE_D] && !InputEvent[SDL_SCANCODE_S])
		{
			ProcessedInputReleases.push_back(SDLK_W);
		}
		if (InputEvent[SDL_SCANCODE_A])
		{
			ProcessedInputEvents.push_back(SDLK_A);
		}
		else if(!InputEvent[SDL_SCANCODE_W] && !InputEvent[SDL_SCANCODE_D] && !InputEvent[SDL_SCANCODE_S])
		{
			ProcessedInputReleases.push_back(SDLK_A);
		}
		if (InputEvent[SDL_SCANCODE_S])
		{
			ProcessedInputEvents.push_back(SDLK_S);
		}
		else if(!InputEvent[SDL_SCANCODE_A] && !InputEvent[SDL_SCANCODE_D] && !InputEvent[SDL_SCANCODE_W])
		{
			ProcessedInputReleases.push_back(SDLK_S);
		}
		if (InputEvent[SDL_SCANCODE_D])
		{
			ProcessedInputEvents.push_back(SDLK_D);
		}
		else if(!InputEvent[SDL_SCANCODE_A] && !InputEvent[SDL_SCANCODE_W] && !InputEvent[SDL_SCANCODE_S])
		{
			ProcessedInputReleases.push_back(SDLK_D);
		}
	}

	

	void HandleInput()
	{
		// Go through all processed Inputs and Try to Execute Input Actions which may bound to them
		for (const auto& InputEvent : ProcessedInputEvents)
		{
			SDL_Keycode CurrentKey = InputEvent;

			if (ActionContext->HasKeycode(CurrentKey))
			{
				if (InputAction* CurrentInputAction = ActionContext->GetInputAction(CurrentKey))
				{
					E_AxisMapping BoundAxis = ActionContext->KeyToAxisMap[CurrentKey];
					CurrentInputAction->GetActionValue().UpdateValue(BoundAxis);
					CurrentInputAction->Execute();
				}
			}
			
		}
		for (const auto& InputRelease : ProcessedInputReleases)
		{
			SDL_Keycode CurrentKey = InputRelease;

			if (ActionContext->HasKeycode(CurrentKey))
			{
				if (InputAction* CurrentInputAction = ActionContext->GetInputAction(CurrentKey))
				{
					CurrentInputAction->GetActionValue().ClearValue();
					CurrentInputAction->Execute();
				}
			}
		}

		// Clear all Inputs
		ProcessedInputEvents.clear();
		ProcessedInputReleases.clear();
	}

private:

	std::vector<SDL_Keycode> ProcessedInputEvents;
	std::vector<SDL_Keycode> ProcessedInputReleases;

	InputActionContext* ActionContext = nullptr;
};
