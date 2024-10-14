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
			
		}

	}
	const bool* keyStates = SDL_GetKeyboardState(NULL);

	SInputSystem.DispatchInputEvent(keyStates);

}

void InputSystem::DispatchInputEvent(const bool* InputEvent)
{
	for (auto& PlayerInputComponent : InputComponents)
			{
				PlayerInputComponent->ReceiveInputEvent(InputEvent);
			}
}

//void InputSystem::DispatchInputEvent(const SDL_Event& InputEvent)
//{
//	for (auto& PlayerInputComponent : InputComponents)
//	{
//		PlayerInputComponent->ReceiveInputEvent(InputEvent);
//	}
//}

//void InputSystem::DispatchInputRelease(const SDL_Event& InputEvent)
//{
//	for (auto& PlayerInputComponent : InputComponents)
//	{
//		PlayerInputComponent->ReceiveInputReleaase(InputEvent);
//	}
//}


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
