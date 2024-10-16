#pragma once
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include <unordered_map>
#include <memory>
#include <functional>
#include "../Subsystem/InputSystem.h"
#include "InputAction.h"
#include "InputActionContext.h"



// Helper struct mapping scancode to keycode
struct KeyBindInfo
{
	KeyBindInfo()
	{
		KeyBindings.insert({
			{SDL_SCANCODE_W, SDLK_W},
			{SDL_SCANCODE_S, SDLK_S},
			{SDL_SCANCODE_A, SDLK_A},
			{SDL_SCANCODE_D, SDLK_D},
			});
	}

	std::unordered_map<SDL_Scancode, SDL_Keycode> KeyBindings;
};

class InputComponent
{
public:
	InputComponent()
	{
		InputSystem::Get().AddInputComponent(this);
	}

	~InputComponent()
	{
		InputSystem::Get().RemoveInputComponent(this);
	}

	void SetInputActionContext(InputActionContext* InActionContext)
	{
		ActionContext = InActionContext;
	}

	void ReceiveMouseEvent(const SDL_Event& MouseEvent)
	{
		ActionContext->HandleMouseEvent(MouseEvent);
	}

	void ReceiveQuitEvent(const SDL_Event& QuitEvent)
	{
		ActionContext->HandleQuitEvent(QuitEvent);
	}

	void ReceiveKeyState(const bool* KeyState)
	{
		for (const auto& KeycodePair : KeyBindInfo.KeyBindings)
		{
			if (KeyState[KeycodePair.first])
			{
				ProcessedInputKeys.push_back(KeycodePair.second);
			}
		}		
	}

	void ReceiveReleaseKey(SDL_Event ReleaseEvent)
	{
		if (!ActionContext->HasKeycode(ReleaseEvent.key.key)) return;
	
		ProcessedReleasedKeys.push_back(ReleaseEvent.key.key);
	}

	void HandleInput()
	{
		for (const auto& InputKey : ProcessedInputKeys)
		{		
			ActionContext->HandleKeyExecution(InputKey);
		}

		for (const auto& InputRelease : ProcessedReleasedKeys)
		{
			ActionContext->HandleKeyRelease(InputRelease);
		}

		// Clear all Inputs
		ProcessedInputKeys.clear();
		ProcessedReleasedKeys.clear();
	}

private:

	std::vector<SDL_Keycode> ProcessedInputKeys;
	std::vector<SDL_Keycode> ProcessedReleasedKeys;


	InputActionContext* ActionContext = nullptr;
	KeyBindInfo KeyBindInfo;
};
