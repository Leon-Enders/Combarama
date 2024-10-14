#include "InputSystem.h"
#include <algorithm>
#include "SDL3/SDL_events.h"
#include "InputComponent.h"


InputSystem InputSystem::SInputSystem;

void InputSystem::HandleInput()
{
	CaptureInput();
	ProcessInputComponents();
}

void InputSystem::CaptureInput()
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_EVENT_KEY_DOWN)
		{
			if (Event.key.key == SDLK_SPACE)
			{
				SDL_Log("Do I have an Delay?");
			}
			SInputSystem.DispatchInputEvent(Event);
		}
	}
}

void InputSystem::DispatchInputEvent(const SDL_Event& InputEvent)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent->ReceiveInputEvent(InputEvent);
	}
}

void InputSystem::ProcessInputComponents()
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent->HandleInput();
	}
}

void InputSystem::AddInputComponent(InputComponent* InputComponentToAdd)
{
	if (InputComponentToAdd)
	{
		InputComponents.push_back(InputComponentToAdd);
	}
}

void InputSystem::RemoveInputComponent(InputComponent* InputComponentToRemove)
{
	
	auto Iterator = std::find(InputComponents.begin(), InputComponents.end(), InputComponentToRemove);

	if (Iterator != InputComponents.end())
	{
		InputComponents.erase(Iterator);
	}
}
