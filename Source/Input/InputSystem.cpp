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
		
	}
	const bool* KeyState = SDL_GetKeyboardState(NULL);

	SInputSystem.DispatchKeyState(KeyState);

}

void InputSystem::DispatchKeyState(const bool* KeyState)
{
	for (auto& PlayerInputComponent : InputComponents)
			{
				PlayerInputComponent->ReceiveKeyState(KeyState);
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
