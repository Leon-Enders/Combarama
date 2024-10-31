#pragma once
#include <vector>
#include <functional>


union SDL_Event;
class InputComponent;

//Singleton Class handeling Input for all InputComponents
class InputSystem
{
public:
	static InputSystem& Get() { return SInputSystem; }

	void HandleInput();

	void AddInputComponent(InputComponent& InputComponentToAdd);
	void RemoveInputComponent(InputComponent& InputComponentToRemove);

public:

	std::function<void(void)> QuitDelegate;
private:
	InputSystem() = default;

	void CaptureInput();
	void DispatchKeyState(const bool* KeyState);
	void DispatchReleasedKey(const SDL_Event& Event);
	void DispatchMouseEvent(const SDL_Event& MouseEvent);
	void DispatchAttackEvent(const SDL_Event& Event);
	void DispatchQuitEvent(const SDL_Event& QuitEvent);
	void ProcessInputComponents();
	

	static InputSystem SInputSystem;
	std::vector<std::reference_wrapper<InputComponent>> InputComponents;
};
