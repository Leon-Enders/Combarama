#pragma once
#include <memory>
#include <vector>
#include <string>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include "Utility/CombaramaStructs.h"
#include "World/World.h"
#include "Coroutine/Task.h"
#include "Coroutine/Awaitable/WaitForDelay.h"


class Game
{
public:
	Game(App& GameApp);

	void StartGame();

	//GameLoop
	void StartGameLoop();

	void GameLoop();
	void ProcessInput();
	void FixedUpdate();
	void Update();
	void Render();


	//Renderer
	void ComposeFrame();
	void RenderFrame();	

	//Temp
	void LoadBackground();
	void QuitGame();
private:

	SDL_Texture* GameBackground = nullptr;
	SDL_Window* GameWindow = nullptr;
	SDL_Renderer* GameRenderer = nullptr;

	bool IsGameActive = false;

	Uint64 FrameStart = 0;
	Uint64 FrameTime = 0;
	float DeltaTimeS = 0;
	float DeltaTimeMS = 0;


	static constexpr int FPS = 120;
	static constexpr int FrameDelay = 1000 / FPS;
	static constexpr int FixedDeltaTimeMS = FrameDelay;
	static constexpr float FixedDeltaTimeS= FixedDeltaTimeMS / 1000.f;
	int FixedTimeCounter = 0;
	static constexpr SDL_FRect BackGround = { 0.f,0.f,1280.f,720 };
	std::string ImagePath;


	//World
	std::unique_ptr<World> GameWorld;


	//Coroutine test
	std::vector<std::coroutine_handle<Task::promise_type>> ActiveCoroutines;

	Task DelayTask()
	{
		SDL_Log("Coroutine started waiting for 2 seconds.");
		co_await WaitForDelay(std::chrono::milliseconds(10000));
		SDL_Log("Coroutine finished.");
	}
};