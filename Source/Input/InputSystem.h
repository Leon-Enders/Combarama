#pragma once
#include <vector>


union SDL_Event;
class InputComponent;

//Singleton Class handeling Input for all InputComponents
class InputSystem
{
public:
	static InputSystem& Get() { return SInputSystem; }

	void HandleInput();

	void AddInputComponent(InputComponent* InputComponentToAdd);
	void RemoveInputComponent(InputComponent* InputComponentToRemove);

private:
	void CaptureInput();
	void DispatchInputEvent(const SDL_Event& InputEvent);
	void ProcessInputComponents();

	static InputSystem SInputSystem;
	std::vector<InputComponent*> InputComponents;
};
