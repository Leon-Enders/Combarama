#include "InputSystem.h"
#include <algorithm>
#include "SDL3/SDL_events.h"
#include "../Input/InputComponent.h"
#include <chrono>

InputSystem InputSystem::SInputSystem;

void InputSystem::HandleInput()
{
	CaptureInput();
	ProcessInputComponents();
}

void InputSystem::CaptureInput()
{
	auto starti = std::chrono::high_resolution_clock::now();
	
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
		else if (Event.type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN)
		{
			DispatchAttackEvent(Event);
		}
	}
	auto endi = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> frameTimei = endi - starti;

	SDL_Log("CaputeInput: %f", frameTimei.count());

	const bool* KeyState = SDL_GetKeyboardState(NULL);

	SInputSystem.DispatchKeyState(KeyState);

}

void InputSystem::DispatchKeyState(const bool* KeyState)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent.get().ReceiveKeyState(KeyState);
	}
}

void InputSystem::DispatchReleasedKey(const SDL_Event& Event)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent.get().ReceiveReleaseKey(Event);
	}
}

void InputSystem::DispatchMouseEvent(const SDL_Event& MouseEvent)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent.get().ReceiveMouseEvent(MouseEvent);
	}
}

void InputSystem::DispatchAttackEvent(const SDL_Event& Event)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent.get().ReceiveAttackEvent(Event);
	}
}

void InputSystem::DispatchQuitEvent(const SDL_Event& QuitEvent)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent.get().ReceiveQuitEvent(QuitEvent);
	}
}


void InputSystem::ProcessInputComponents()
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent.get().HandleInput();
	}
}

void InputSystem::AddInputComponent(InputComponent& InputComponentToAdd)
{
	InputComponents.push_back(std::ref(InputComponentToAdd));
}

void InputSystem::RemoveInputComponent(InputComponent& InputComponentToRemove)
{
	InputComponents.erase(
		std::remove_if(InputComponents.begin(), InputComponents.end(),
			[&](std::reference_wrapper<InputComponent> component) {
				return &component.get() == &InputComponentToRemove;
			}),
		InputComponents.end());
}
