#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../Core/Misc/CombaramaStructs.h"
#include "GameFramework/World/World.h"
#include "Render/RenderSubsystem.h"


class Game
{
public:
	Game(App& GameApp);

	void Initialize();
	void StartGame();
	inline RenderSubsystem* GetRenderSubsystem() { return RS.get(); }

private:
	
	//GameLoop
	void StartGameLoop();

	void GameLoop();
	void ProcessInput();
	void LateUpdate();
	void Update();
	void FixedUpdate();
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

	std::unique_ptr<RenderSubsystem> RS;
};