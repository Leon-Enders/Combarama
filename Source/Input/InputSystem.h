#pragma once
#include <vector>
#include "SDL3/SDL_events.h"

class InputComponent;

//Singleton Class handeling Input for all InputComponents
class InputSystem
{
public:
	static InputSystem& Get() { return SInputSystem; }

	void ProcessInputEvent(const SDL_Event& InputEvent);
	void HandleInput();

	void AddInputComponent(InputComponent* InputComponentToAdd);
	void RemoveInputComponent(InputComponent* InputComponentToRemove);
private:
	
	
	static InputSystem SInputSystem;

	std::vector<InputComponent*> InputComponents;
};
