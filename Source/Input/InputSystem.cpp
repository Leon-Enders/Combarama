#include "InputSystem.h"
#include "InputComponent.h"
#include <algorithm>


InputSystem InputSystem::SInputSystem;

void InputSystem::ProcessInputEvent(const SDL_Event& InputEvent)
{
	for (auto& PlayerInputComponent : InputComponents)
	{
		PlayerInputComponent->ReceiveInputEvent(InputEvent);
	}
}

void InputSystem::HandleInput()
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
