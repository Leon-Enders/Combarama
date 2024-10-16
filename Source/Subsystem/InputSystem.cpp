#include "InputSystem.h"
#include <algorithm>
#include "SDL3/SDL_events.h"
#include "../Input/InputComponent.h"


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
		if (Event.type == SDL_EventType::SDL_EVENT_QUIT)
		{
			DispatchQuitEvent(Event);
		}
		else if (Event.type == SDL_EventType::SDL_EVENT_MOUSE_MOTION)
		{
			DispatchMouseEvent(Event);
		}
		else if (Event.type == SDL_EventType::SDL_EVENT_KEY_UP)
		{
			DispatchReleasedKey(Event);
		}
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

void InputSystem::DispatchReleasedKey(const SDL_Event& Event)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent->ReceiveReleaseKey(Event);
	}
}

void InputSystem::DispatchMouseEvent(const SDL_Event& MouseEvent)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent->ReceiveMouseEvent(MouseEvent);
	}
}

void InputSystem::DispatchQuitEvent(const SDL_Event& QuitEvent)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent->ReceiveQuitEvent(QuitEvent);
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
