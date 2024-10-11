#pragma once
#include <memory>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include "CombaramaStructs.h"
#include "Actor.h"




class Game
{
public:
	Game(App& GameApp);

	void StartGame();
	

	//GameLoop
	void HandleGameLoop();
	void ProcessInput();
	void Update();
	void Render();


	//Renderer
	void ComposeFrame();
	void RenderFrame();

private:

	SDL_Window* GameWindow = nullptr;
	SDL_Renderer* GameRenderer = nullptr;

	SDL_Event Event = SDL_Event();

	bool IsGameActive = false;

	Uint64 FrameStart = 0;
	int FrameTime = 0;
	int DeltaTime = 0;


	static constexpr int FPS = 60;
	static constexpr int FrameDelay = 1000 / FPS;

	std::unique_ptr<Actor> Player = nullptr;

};