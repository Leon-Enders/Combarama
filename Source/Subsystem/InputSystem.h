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
	InputSystem() = default;

	void CaptureInput();
	void DispatchKeyState(const bool* KeyState);
	void DispatchReleasedKey(const SDL_Event& Event);
	void DispatchMouseEvent(const SDL_Event& MouseEvent);
	void DispatchQuitEvent(const SDL_Event& QuitEvent);
	void ProcessInputComponents();
	

	static InputSystem SInputSystem;
	std::vector<InputComponent*> InputComponents;
};
